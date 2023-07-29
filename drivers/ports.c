#include "ports.h"

uint8_t inportb(uint16_t port)
{
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void outportb(uint16_t port, uint8_t data)
{
    asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}