#include "sbi.h"

#include <asm/sbi.h>
#include <asm/page.h>
#include <linux/kernel.h>

#define FID_ENTRY(name_val, fid_val) { \
	.attribute = { .attr = { .name = (name_val), .mode = S_IRUGO }, \
	               .show = sbi_attr_show }, \
	.fid = (fid_val) \
}

struct sbi_fid_entry sbi_probe_list[] = {
	FID_ENTRY("sbi_spec_version", SBI_EXT_BASE_GET_SPEC_VERSION),
	FID_ENTRY("sbi_imp_id", SBI_EXT_BASE_GET_IMP_ID),
	FID_ENTRY("sbi_imp_version", SBI_EXT_BASE_GET_IMP_VERSION),
	FID_ENTRY("mvendorid", SBI_EXT_BASE_GET_MVENDORID),
	FID_ENTRY("marchid", SBI_EXT_BASE_GET_MARCHID),
	FID_ENTRY("mimpid", SBI_EXT_BASE_GET_MIMPID),
	FID_ENTRY(NULL, 0)
};

static long base_name_to_fid(const char *name) {
	struct sbi_fid_entry *ent;

	for (ent = sbi_probe_list; ent->attribute.attr.name; ent ++)
		if (strcmp(ent->attribute.attr.name, name) == 0)
			return ent->fid;

	return -EINVAL;
}

ssize_t sbi_attr_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct sbiret ret;
	long fid;

	fid = base_name_to_fid(attr->attr.name);

	if (fid < 0)
		return (ssize_t) fid;

	ret = sbi_ecall(SBI_EXT_BASE, fid, 0, 0, 0, 0, 0, 0);

	if (ret.error)
		return sbi_err_map_linux_errno(ret.error);

	return sysfs_emit(buf, "0x%lx\n", ret.value);
}
