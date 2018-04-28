
CXX=i686-elf-g++
AS=i686-elf-as

CXXFLAGS=-g -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -ffreestanding
KERNELFLAGS=-g -ffreestanding -O2 -nostdlib
KERNELLIBS=-lgcc

CRTBEGIN_OBJ:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)

all: myos.bin

run: myos.bin
	qemu-system-i386 -cdrom myos.iso

myos.bin: kernel.o boot.o terminal.o utils.o vga.o
	$(CXX) -T linker.ld $(KERNELFLAGS) $^ -o $@ $(KERNELLIBS)
	~/opt/cross/i686-elf/bin/objcopy --only-keep-debug $@ kernel.sym
	~/opt/cross/i686-elf/bin/objcopy --strip-debug $@
	if grub-file --is-x86-multiboot myos.bin; then echo multiboot confirmed; else echo the file is not multiboot; fi
	mkdir -p isodir/boot/grub
	cp $@ isodir/boot/$@
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

kernel.o: kernel.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

boot.o: boot.s
	$(AS) boot.s -o $@

terminal.o: terminal.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

utils.o: utils.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

vga.o: vga.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -rf *.o myos.iso boot.o myos.bin kernel.sym isodir
