#include "string.h"


void itoa(int n, char* s)
{
    int sign;
    if ((sign = n) < 0) n = -n;

    int i = 0;
    do
    {
        s[i++] = '0' + (n % 10);
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

int strlen(char* s)
{
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char* s)
{
    int i, j;
    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j)
    {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
};