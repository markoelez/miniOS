#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../cpu/isr.h"
#include "../libc/string.h"


void main()
{
    isr_install();
    irq_install();

    kprint("Type QUIT to quit\n> ");
}