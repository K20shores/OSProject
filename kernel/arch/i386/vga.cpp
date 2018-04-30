#include <kernel/vga.h>

VGA::VGA()
    : _width(80)
    , _height(25)
{
}

uint8_t VGA::entry_color(vga_color fg, vga_color bg)
{
    return fg | bg << 4;
}

uint16_t VGA::entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t VGA::height()
{
    return _height;
}

size_t VGA::width()
{
    return _width;
}
