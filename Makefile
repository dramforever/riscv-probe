MODULE = riscv-probe

obj-m := $(MODULE).o

$(MODULE)-objs = main.o sbi.o
