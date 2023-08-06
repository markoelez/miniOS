#include <kernel/screen.h>
#include <libc/string.h>
#include <stdbool.h>


void kernel_main()
{
    // TODO: add graphical mode support.
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
}