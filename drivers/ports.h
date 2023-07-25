#ifndef PORTS_H
#define PORTS_H

#include "../cpu/util.h"

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

#endif