#include <libc/mem.h>


void memcpy(void* dst, const void* src, size_t nbytes)
{
    const char* csrc = (const char*)src;
    char* cdst = (char*)dst;
    for (size_t i = 0; i < nbytes; ++i) *(cdst + i) = *(csrc + i);
};