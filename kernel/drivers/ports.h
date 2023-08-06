#ifndef PORTS_H
#define PORTS_H

#include <kernel/util.h>

#include <stdint.h>

uint8_t inportb(uint16_t port);
void outportb(uint16_t port, uint8_t data);

#endif