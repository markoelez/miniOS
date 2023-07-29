#include "timer.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

uint32_t tick = 0;

static void timer_callback(__attribute__((unused)) registers_t* regs)
{
    ++tick;
}

void init_timer(uint32_t freq)
{

    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outportb(0x43, 0x36);
    outportb(0x40, low);
    outportb(0x40, high);
}
