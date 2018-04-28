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
    init_screen();
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
    init_screen();
}

void Terminal::init_screen()
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
    column = 0;
    if (++row == vga.height())
    {
        scroll_up();
        --row;
    }
}

void Terminal::putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * vga.width() + x;
    buffer[index] = vga.entry(c, color);
}

void Terminal::scroll_up()
{
    /* move all contents of the screen up one line */
    for (size_t y = 0; y < vga.height(); ++y)
    {
        for (size_t x = 0; x < vga.width(); ++x)
        {
            const size_t old_char = y * vga.width() + x;
            const size_t new_char = (y + 1) * vga.width() + x;
            buffer[old_char] = buffer[new_char];
        }
    }
    /* write the blank character on the last line */
    for (size_t x = 0; x < vga.width(); ++x)
    {
        const size_t index = (vga.height() - 1) * vga.width() + x;
        buffer[index] = vga.entry(' ',  color);
    }
}

void Terminal::putchar(char c)
{
    if (c == '\n')
    {
        newline();
        return;
    }
    putentryat(c, color, column, row);
    if (++column == vga.width())
    {
        newline();
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
