#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"


void user_input(char* input)
{
    if (strcmp(input, "QUIT") == 0)
    {
        kprint("Exitting...\n");
        asm volatile("hlt");
    }

    kprint("[INPUT]: ");
    kprint(input);
    kprint("\n> ");
}