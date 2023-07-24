#include "libc.h"


void itoa(int n, char str[])
{
    int sign;
    if ((sign = n) < 0) n = -n;

    int i = 0;
    do
    {
        str[i++] = '0' + (n % 10);
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}
