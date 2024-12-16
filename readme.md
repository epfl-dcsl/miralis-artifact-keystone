# Keystone Artifact

This repository automates the build of [Keystone](https://keystone-enclave.org/) for the purpose of generating artifacts that can be used for integration tests in the Miralis project.

## How to release new artifacts

Create a new tag and push it to upstream, e.g.:

```sh
git tag v0.1.0
git push origin v0.1.0
```

## Artifacts
TODO: Double check the content of keystone.img

`keystone.img`: A linux kernel with the keystone driver. To install the driver, run `modprobe keystone-driver`.

`keystone.ext2`: A disk image that contains examples of enclave application in the `/usr/share/keystone/examples` directory.

For example, to run the `hello.ke` enclave on qemu, you can:
1. Load `miralis` and `keystone.img` into qemu.
2. Attach the `keystone.ext2` disk image to qemu.

The above steps can be done by running 
```sh
qemu-system-riscv64 --no-reboot -nographic -machine virt -bios /path/to/miralis.img -device loader,file=/path/to/keystone.img,addr=0x80200000,force-raw=on -smp 1 -drive file=path/to/keystone.ext2,format=raw,id=hd0 -device virtio-blk-device,drive=hd0 -device virtio-net-device
```
3. Run `modprobe keystone-driver` to load the Keystone driver
4. Run `/usr/share/keystone/examples/hello.ke` to run the enclave. A hello world message should appear.