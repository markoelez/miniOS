#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include <stdbool.h>


void kernel_main()
{
    bool tm = true;

    clear_screen();

    if (tm)
    {
        kprint("Starting in text mode...\n");
    }
    else
    {
        kprint("Starting in graphical mode...\n");
    }

    kprint("MiniOS v0.1\n\n");

    isr_install();
    irq_install();
}