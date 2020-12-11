// setup env:
// assemble the boot file
// nasm boot/boot.S -o boot.o 
//
// compile the kernel
// gcc -c kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
// grub-file --is-x86-multiboot myos.bin

/*

mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir

qemu-system-i386 -cdrom myos.iso


qemu-system-i386 -kernel myos.bin
sudo dd if=myos.iso of=/dev/sdx && sync


*/