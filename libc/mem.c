#include "mem.h"


void memcpy(void* dst, const void* src, int nbytes)
{
    const char* csrc = (const char*)src;
    char* cdst = (char*)dst;
    for (int i = 0; i < nbytes; ++i) *(cdst + i) = *(csrc + i);
};