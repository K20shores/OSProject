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
}
