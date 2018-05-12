#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>

TTY* kernel_tty;

extern "C" void kernel_main(void) {
    /* kernel setup */
    // initialize the GDT and TTY
    TTY tty; 
    GDT gdt; 

    // make the tty available to put
    kernel_tty = &tty;

	printf("Hello, kernel World!\n");
    printf("a\n");
    printf("b\n");
    printf("c\n");
    printf("d\n");
    printf("e\n");
    printf("f\n");
    printf("g\n");
    printf("h\n");
    printf("i\n");
    printf("j\n");
    printf("k\n");
    printf("l\n");
    printf("m\n");
    printf("n\n");
    printf("o\n");
    printf("p\n");
    printf("q\n");
    printf("r\n");
    printf("s\n");
    printf("t\n");
    printf("u\n");
    printf("v\n");
    printf("w\n");
    printf("x\n");
    printf("y\n");
    printf("z\n");
	printf("Goodbye, kernel World!");
}
