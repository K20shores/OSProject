
OSNAME=DevOS
CXX=i686-elf-g++
AS=i686-elf-as

CXXFLAGS=-g -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -ffreestanding
KERNELFLAGS=-g -ffreestanding -O2 -nostdlib
KERNELLIBS=-lgcc

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

OBJS=kernel.o boot.o terminal.o utils.o vga.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

all: $(OSNAME).bin

run: $(OSNAME).bin
	qemu-system-i386 -cdrom $(OSNAME).iso

$(OSNAME).bin: $(OBJS)
	$(CXX) -T linker.ld $(KERNELFLAGS) $^ -o $@ $(KERNELLIBS)
	~/opt/cross/i686-elf/bin/objcopy --only-keep-debug $@ kernel.sym
	~/opt/cross/i686-elf/bin/objcopy --strip-debug $@
	if grub-file --is-x86-multiboot $(OSNAME).bin; then echo multiboot confirmed; else echo the file is not multiboot; fi
	mkdir -p isodir/boot/grub
	cp $@ isodir/boot/$@
	echo "menuentry \""$(OSNAME)"\"{ multiboot /boot/"$(OSNAME)".bin}" >> isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(OSNAME).iso isodir

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
	rm -rf $(INTERNAL_OBJS) $(OSNAME).iso $(OSNAME).bin kernel.sym isodir
