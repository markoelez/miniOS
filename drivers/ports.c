#include "ports.h"

uint8 port_byte_in (uint16 port)
{
    uint8 result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (uint16 port, uint8 data)
{
    asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}