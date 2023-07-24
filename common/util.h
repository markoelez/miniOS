#ifndef UTIL_H
#define UTIL_H

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char uint8;
typedef char int8;

#define low_16(addr) (uint16)((addr) & 0xFFFF)
#define high_16(addr) (uint16)(((addr) >> 16) & 0xFFFF)

#endif