#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define low_16(addr) (uint16_t)((addr) & 0xFFFF)
#define high_16(addr) (uint16_t)(((addr) >> 16) & 0xFFFF)

#endif