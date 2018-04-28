#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils.h"
#include "terminal.h"

/* Check if the compiler thinks we are targeting the wrong operatin system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial wil only work fro the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


extern "C" void kernel_main(void)
{
    Terminal terminal;
    terminal.write_string("Hello, kernel World!\n");
    terminal.write_string("This is a test sentence. This is a test sentence. This is a test sentence. This is a test sentence. This is a test sentence.\n");
    terminal.write_string("a\n");
    terminal.write_string("b\n");
    terminal.write_string("c\n");
    terminal.write_string("d\n");
    terminal.write_string("e\n");
    terminal.write_string("f\n");
    terminal.write_string("g\n");
    terminal.write_string("Hello, kernel World!1\n");
    terminal.write_string("Hello, kernel World!2\n");
    terminal.write_string("Hello, kernel World!3\n");
    terminal.write_string("Hello, kernel World!4\n");
    terminal.write_string("Hello, kernel World!5\n");
    terminal.write_string("Hello, kernel World!6\n");
    terminal.write_string("Hello, kernel World!7\n");
    terminal.write_string("Hello, kernel World!8\n");
    terminal.write_string("Hello, kernel World!9\n");
    terminal.write_string("Hello, kernel World!10\n");
    terminal.write_string("Hello, kernel World!11\n");
    terminal.write_string("Hello, kernel World!12\n");
    terminal.write_string("Hello, kernel World!13\n");
    terminal.write_string("h\n");
    terminal.write_string("i\n");
    terminal.write_string("j\n");
    terminal.write_string("Hello, kernel World!6\n");
    terminal.write_string("Hello, kernel World!7\n");
    terminal.write_string("Hello, kernel World!8\n");
}
