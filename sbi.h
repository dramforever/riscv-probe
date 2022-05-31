#ifndef RISCV_PROBE_SBI_H
#define RISCV_PROBE_SBI_H

#include <linux/kobject.h>

struct sbi_fid_entry {
	struct kobj_attribute attribute;
	long fid;
};

extern struct sbi_fid_entry sbi_probe_list[];

ssize_t sbi_attr_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);

#endif /* RISCV_PROBE_SBI_H */
