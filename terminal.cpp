#include "terminal.h"
#include "utils.h"

Terminal::Terminal()
    : vga()
    , fg(vga_color::VGA_COLOR_LIGHT_GREY)
    , bg(vga_color::VGA_COLOR_BLACK)
    , row(0)
    , column(0)
    , color(vga.entry_color(fg, bg))
    , buffer((uint16_t*) 0xB8000)
{
    for (size_t y = 0; y < vga.height(); ++y)
    {
        for (size_t x = 0; x < vga.width(); ++x)
        {
            const size_t index = y * vga.width() + x;
            buffer[index] = vga.entry(' ', color);
        }
    }
}

Terminal::Terminal(vga_color fg, vga_color bg)
    : vga()
    , fg(fg)
    , bg(bg)
    , row(0)
    , column(0)
    , color(vga.entry_color(fg, bg))
    , buffer((uint16_t*) 0xB8000)
{
    for (size_t y = 0; y < vga.height(); ++y)
    {
        for (size_t x = 0; x < vga.width(); ++x)
        {
            const size_t index = y * vga.width() + x;
            buffer[index] = vga.entry(' ', color);
        }
    }
}


void Terminal::setcolor(uint8_t color)
{
    this->color = color;
}

void Terminal::newline()
{
    if (++row == vga.height())
    {
        row = 0;
    }
    column = 0;
}

void Terminal::putentryat(char c, uint8_t color, size_t x, size_t y)
{
    if (c == ' ')
    {
        newline();
    }
    const size_t index = y * vga.width() + x;
    buffer[index] = vga.entry(c, color);
}

void Terminal::putchar(char c)
{
    putentryat(c, color, column, row);
    if (++column == vga.width())
    {
        column = 0;
        if (++row == vga.height())
        {
            row = 0;
        }
    }
}

void Terminal::write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        putchar(data[i]);
    }
}

void Terminal::write_string(const char* data)
{
    write(data, strlen(data));
}
