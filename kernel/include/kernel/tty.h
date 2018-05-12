#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/vga.h>

class TTY
{
    public:
        TTY();
        TTY(vga_color fg, vga_color bg);

        void write_string(const char* data);
        void write_char(const char* data, size_t size);
        void clear();

    private:
        /* Functions */
        void setcolor(uint8_t color);
        void newline();
        void putchar(char c);
        void putentryat(char c, uint8_t color, size_t x, size_t y);
        void write(const char* data, size_t size);
        void init_screen();
        void scroll_up();
        void move_cursor();

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
