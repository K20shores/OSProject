#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"

class Terminal
{
    public:
        Terminal();
        Terminal(vga_color fg, vga_color bg);

        void write_string(const char* data);

    private:
        /* Functions */
        void setcolor(uint8_t color);
        void newline();
        void write(const char* data, size_t size);
        void putchar(char c);
        void putentryat(char c, uint8_t color, size_t x, size_t y);

    private:
        /* Data */
        VGA vga;
        vga_color fg;
        vga_color bg;

        size_t row;
        size_t column;
        uint8_t color;
        /* Note the use of the volatile keyword to prevent the compiler from eliminating dead stores. */
        volatile uint16_t* buffer;
};

#endif /* TERMINAL_H */
