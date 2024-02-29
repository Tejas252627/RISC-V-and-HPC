
This document describes the process of rebuilding process on Fedora 38 for RISCV image.

#### Install QEMU on host machine

```sh
sudo dnf install qemu
```

If you are not on Fedora, you can use your package manager to install qemu ,for eg `apt`. On debian based systems you might additional packages for running qemu-system-riscv64

---

#### Download the raw image and supplementary files

At the time of writing, this was downloaded from:

https://dl.fedoraproject.org/pub/alt/risc-v/disk_images/Fedora-Developer-38-20230519.n.0.SiFive.Unmatched.and.QEMU/
 
This repository has images for qemu and sifive unleashed board, we download the qemu specific images, which include :

- Raw disk image (kernel+rootfs)
- Uboot SPL : The first stage bootloader 
- Image Tree Blob (ITB) (opensbi + uboot-proper)

```sh
mkdir Fedora-RISCV-image

cd Fedora-RISCV-image

wget https://dl.fedoraproject.org/pub/alt/risc-v/disk_images/Fedora-Developer-38-20230519.n.0.SiFive.Unmatched.and.QEMU/Fedora-Developer-38-20230519.n.0-qemu.raw.img.xz

wget https://dl.fedoraproject.org/pub/alt/risc-v/disk_images/Fedora-Developer-38-20230519.n.0.SiFive.Unmatched.and.QEMU/Fedora-Developer-38-20230519.n.0-u-boot-spl.bin.xz

wget https://dl.fedoraproject.org/pub/alt/risc-v/disk_images/Fedora-Developer-38-20230519.n.0.SiFive.Unmatched.and.QEMU/Fedora-Developer-38-20230519.n.0-u-boot.itb.xz

```

You may make a backup of tarballs if you wish.

---


#### Extract tarballs

```sh
unxz *
```

This will untar everything in directory and delete the tarballs.

  OR
  
```sh
tar -xvJf *
```

This will extract and preserve the tarballs.

---

#### Expand the image

In order to rebuild packages inside the VM, extra space might be deemed necessary, so we should resize the image.

**If you are on Fedora : **

The following package is a wrapper utility, the underlying command is just `resize2fs`

```sh
sudo dnf install libguestfs-tools-c
```


```sh
truncate -r Fedora-Developer-*.raw.img expanded.raw.img

truncate -s 50G expanded.raw.img

virt-resize -v -x --expand /dev/sda2 Fedora-Developer-*.raw.img expanded.raw.img

virt-filesystems --long -h --all -a expanded.raw.img

virt-df -h -a expanded.raw.img
```

---

#### Create a qemu script to boot the image

```sh
qemu-system-riscv64 \
  -bios Fedora-Developer-38-20230519.n.0-u-boot-spl.bin \
  -nographic \
  -machine virt \
  -smp 8 \
  -m 8G \
  -device loader,file=Fedora-Developer-38-20230519.n.0-u-boot.itb,addr=0x80200000 \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-blk-device,drive=hd0 \
  -drive file=expanded.raw.img,format=raw,id=hd0 \
  -device virtio-net-device,netdev=usernet \
  -netdev user,id=usernet,hostfwd=tcp::10000-:22
```

Make the script *qemurun.sh* executable
```sh
chmod u+x qemurun.sh
```


The prominently modifiable parameters of the command are :

- `-smp n` : Provide the number of cores you wish to pass to the VM. You have a higher chance to pass more than 8 cores if you have the latest version of QEMU
- `-m xG` : Pass the amount of memory (RAM) in gigabytes to the VM.
- `-netdev` : Here we are using user level networking(read SLIRP) as network backend and forwarding tcp port 22 to 10000. If host machine is already running an instance of VM, you would have to change the port map for eg `10006-:22`


#### Boot the image


```sh
./qemurun.sh
```

---

## Post boot

Once booted, you can login as either **root** or the user **riscv** (already in wheel group).
Default passwords for both are **fedora_rocks!**

If you wish to SSH into the VM :

```sh
ssh -p 10000 riscv@localhost
```

