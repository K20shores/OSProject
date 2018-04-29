#include <stdio.h>

#include <kernel/tty.h>

TTY tty;

extern "C" void kernel_main(void) {
	printf("Hello, kernel World!\n");
}
