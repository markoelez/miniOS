#include <kernel/screen.h>
#include <kernel/ports.h>
#include <libc/string.h>
#include <libc/mem.h>

#include <stdint.h>
#include <stddef.h>


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
    outportb(REG_SCREEN_CTRL, 14);
    int offset = inportb(REG_SCREEN_DATA) << 8;
    outportb(REG_SCREEN_CTRL, 15);
    offset += inportb(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    outportb(REG_SCREEN_CTRL, 14);
    outportb(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    outportb(REG_SCREEN_CTRL, 15);
    outportb(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

int print_char(char c, int row, int col, char attr)
{
    unsigned char* screen = (unsigned char*)VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS)
    {
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
    else if (c == 0x08)
    {
        screen[offset] = ' ';
        screen[offset + 1] = attr;
    }
    else
    {
        screen[offset] = c;
        screen[offset + 1] = attr;
        offset += 2;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
        size_t i;
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

    size_t i = 0;
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

void kprint_bs()
{
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, row, col, WHITE_ON_BLACK);
}

void clear_screen()
{
    size_t screen_size = MAX_ROWS * MAX_COLS;
    char* screen = VIDEO_ADDRESS;

    for (size_t i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
    }
    set_cursor_offset(get_offset(0, 0));
};