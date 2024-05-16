all: opensbi.bin

CROSS_COMPILE = riscv64-linux-gnu-
PATCHES = ../mirage_firmware.patch

ifeq ($(shell uname -o), Darwin)
	CROSS_COMPILE = riscv64-elf-
	PATCHES += ../mirage_firmware_macos.patch
endif

opensbi:
	git clone --depth 1 --branch v1.4 https://github.com/riscv-software-src/opensbi.git
	cd opensbi && git apply $(PATCHES)

opensbi.bin: opensbi
	make -C opensbi PLATFORM=generic FW_PAYLOAD=y FW_DYNAMIC=n FW_JUMP=n CROSS_COMPILE=$(CROSS_COMPILE) -j`nproc`
	cp opensbi/build/platform/generic/firmware/fw_payload.bin opensbi.bin
	cp opensbi/build/platform/generic/firmware/fw_payload.elf opensbi.elf

.PHONY: clean
clean:
	rm -rf opensbi opensbi.bin opensbi.elf
