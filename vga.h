#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

/* Hardware text mode color constants. */
enum vga_color{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

class VGA
{
    public:
        VGA();
        uint8_t entry_color(vga_color fg, vga_color bg);
        uint16_t entry(unsigned char uc, uint8_t color);

        size_t height();
        size_t width();

    private:
        const size_t _width;
        const size_t _height;
};

#endif /* VGA_H */
