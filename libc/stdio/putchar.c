#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

extern TTY* kernel_tty;

int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
    kernel_tty->write_char(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
