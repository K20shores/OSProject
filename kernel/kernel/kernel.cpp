#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

TTY* kernel_tty;

extern "C" void kernel_main(void) {
    // setup the TTY
    TTY tty; 
    kernel_tty = &tty;

    // initialize the GDT and IDT
    GDT gdt; 
    IDT idt;

    // make the tty available to put

	printf("Hello, kernel World!\n");
	printf("Goodbye, kernel World!");
}
