#include "timer.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../kernel/libc.h"

uint32 tick = 0;

static void timer_callback(registers_t regs)
{
    kprint("Tick: ");
    char tick_ascii[256];
    itoa(++tick, tick_ascii);
    kprint(tick_ascii);
    kprint("\n");
}

void init_timer(uint32 freq)
{

    register_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = 1193180 / freq;
    uint8 low  = (uint8)(divisor & 0xFF);
    uint8 high = (uint8)((divisor >> 8) & 0xFF);
    
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
