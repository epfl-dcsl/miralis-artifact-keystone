obj-m += driver.o

CROSS_COMPILE = riscv64-unknown-linux-gnu-

all:
	make -C ../linux M=$(PWD) modules ARCH=riscv CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C ../linux M=$(PWD) clean