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

int strcmp(char* a, char* b)
{
    int i;
    for (i = 0; a[i] == b[i]; ++i)
        if (a[i] == '\0') return 0;
    return a[i] - b[i];
}

void pop(char* s)
{
    s[strlen(s) - 1] = '\0';
}

void append(char* s, char c)
{
    int n = strlen(s);
    s[n] = c;
    s[n + 1] = '\0';
}