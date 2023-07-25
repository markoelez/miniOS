#include "screen.h"
#include "ports.h"
#include "../libc/string.h"
#include "../libc/mem.h"


int get_offset(int row, int col)
{
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

int get_cursor_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8)(offset & 0xff));
}

int print_char(char c, int row, int col, char attr)
{
    unsigned char* screen = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        screen[2 * MAX_ROWS * MAX_COLS - 2] = 'E';
        screen[2 * MAX_ROWS * MAX_COLS - 1] = RED_ON_WHITE;
        return get_offset(row, col);
    }

    int offset;
    if (row >= 0 && col >= 0) offset = get_offset(row, col);
    else offset = get_cursor_offset();

    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(row + 1, 0);
    }
    else
    {
        screen[offset] = c;
        screen[offset + 1] = attr;
        offset += 2;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
        int i;
        for (i = 1; i < MAX_ROWS; ++i) 
            memcpy((void*)(get_offset(i - 1, 0) + VIDEO_ADDRESS),
                   (void*)(get_offset(i, 0) + VIDEO_ADDRESS),
                   MAX_COLS * 2);

        char* last_line = (char*)(get_offset(MAX_ROWS - 1, 0) + VIDEO_ADDRESS);
        for (i = 0; i < MAX_COLS * 2; ++i)
            last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}


void kprint_at(char* str, int row, int col)
{
    int offset;
    if (row >= 0 && col >= 0)
    {
        offset = get_offset(row, col);
    }
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (str[i] != 0)
    {
        offset = print_char(str[i++], row, col, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char* str)
{
    kprint_at(str, -1, -1);
}

void clear_screen()
{
    int screen_size = MAX_ROWS * MAX_COLS;
    char* screen = VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
};