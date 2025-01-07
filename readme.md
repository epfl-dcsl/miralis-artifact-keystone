# Keystone Artifact

This repository automates the build of [Keystone](https://keystone-enclave.org/) for the purpose of generating artifacts that can be used for integration tests in the Miralis project.

## How to release new artifacts

Create a new tag and push it to upstream, e.g.:

```sh
git tag v0.1.0
git push origin v0.1.0
```

## Artifacts

**iozone**: A statically compiled binary of the iozone benchmark

**Image_keystone**: A linux kernel with the keystone driver. To install the driver, run `modprobe keystone-driver`.

**keystone.ext2**: A disk image that contains examples of enclave application in the `/usr/share/keystone/examples` directory. It also contains the iozone binary

**opensbi-linux-keystone.**: An opensbi binary that will jump to the `Image_keystone` payload


## Example
Below is an example on how to run the `hello.ke` enclave on qemu.


```sh
# Load `miralis` and `opensbi-linux-keystone.bin` into qemu, and attach the `keystone.ext2` disk image.
qemu-system-riscv64 --no-reboot -nographic -machine virt -bios /path/to/miralis.img -device loader,file=/path/to/opensbi-linux-keystone.bin,addr=0x80200000,force-raw=on -smp 1 -drive file=path/to/keystone.ext2,format=raw,id=hd0 -device virtio-blk-device,drive=hd0 -device virtio-net-device

# At this point you should be inside the emulated kernel

# Load the keystone driver
modprobe keystone-driver

# Run the enclave. A hello world message should appear
/usr/share/keystone/examples/hello.ke

```
