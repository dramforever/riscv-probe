# riscv-probe

Show some low level system information in `/sys/firmware/riscv`.

## Example

```console
$ ls /sys/firmware/riscv
marchid           mvendorid         sbi_imp_version
mimpid            sbi_imp_id        sbi_spec_version
$ cat /sys/firmware/riscv/sbi_imp_id 
0x1
```
