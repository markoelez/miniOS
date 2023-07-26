#include "keyboard.h"
#include "screen.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "../kernel/shell.h"
#include "../libc/string.h"

#define SC_MAX 57
#define BACKSPACE 0x0E
#define ENTER 0x1C

static char buff[256];

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?',
                          'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
                          'O', 'P', '[', ']', '?', '?', 'A', 'S',
                          'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
                          '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                          'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' ' };

static void keyboard_callback(__attribute__((unused)) registers_t regs)
{
    uint8 sc = port_byte_in(0x60);

    if (sc > SC_MAX) return;

    if (sc == BACKSPACE)
    {
        if (strlen(buff) == 0)
            return;

        pop(buff);
        kprint_bs();
        return;
    }

    if (sc == ENTER)
    {
        kprint("\n");
        user_input(buff);
        buff[0] = '\0';
        return;
    }

    char c = sc_ascii[(int)sc];
    char str[2] = { c, '\0' };
    append(buff, c);
    kprint(str);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}