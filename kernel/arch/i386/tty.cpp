#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/utils.h>

TTY::TTY()
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

TTY::TTY(vga_color fg, vga_color bg)
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

void TTY::init_screen()
{
    for (size_t y = 0; y < vga.height(); ++y)
    {
        for (size_t x = 0; x < vga.width(); ++x)
        {
            const size_t index = y * vga.width() + x;
            buffer[index] = vga.entry(' ', color);
        }
    }
    move_cursor();
}

void TTY::setcolor(uint8_t color)
{
    this->color = color;
}

void TTY::newline()
{
    column = 0;
    if (++row == vga.height())
    {
        scroll_up();
        --row;
    }
}

void TTY::putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * vga.width() + x;
    buffer[index] = vga.entry(c, color);
}

void TTY::scroll_up()
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

void TTY::putchar(char c)
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

void TTY::move_cursor()
{
    const size_t index = row * vga.width() + column;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

void TTY::write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        putchar(data[i]);
    }
    move_cursor();
}

void TTY::write_string(const char* data)
{
    write(data, strlen(data));
}

void TTY::write_char(const char* data, size_t size)
{
    write(data, size);
}

void TTY::clear()
{
    init_screen();
}
