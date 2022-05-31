/* SPDX-License-Identifier: GPL-2.0 */

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>

#include <asm/sbi.h>

#include "sbi.h"

#define MODULE_NAME "hello"

static struct kobject *riscv_kobject;

static int __init riscv_probe_init(void)
{
	int error;
	struct sbi_fid_entry *ent;

	riscv_kobject = kobject_create_and_add("riscv", firmware_kobj);

	if (! riscv_kobject)
		return -ENOMEM;

	for (ent = sbi_probe_list; ent->attribute.attr.name; ent ++)
	{
		error = sysfs_create_file(riscv_kobject, &ent->attribute.attr);
		if (error)
			return error;
	}

	return 0;
}

static void __exit riscv_probe_cleanup(void) {
	kobject_put(riscv_kobject);
}

module_init(riscv_probe_init);
module_exit(riscv_probe_cleanup);

MODULE_LICENSE("GPL");
