#include <stdio.h>
#include <string.h>

void swap (void* a, void* b, size_t n);

int main()
{
    char a[3][32] = {"hello", "manfdgf", "fdsfgdsfdsfdsa" };
    char b[3][32] = {"dsagew", "fsagwwr ewqewq", "ewqrqtfgskofsdko" };

    size_t n = sizeof(a[0]);

    puts(a[0]);
    puts(b[0]);
    swap(a[0], b[0], n);
    puts(a[0]);
    puts(b[0]);
    printf("%u ", n);

}

void swap(void* a, void* b, size_t MemSize)
{
    size_t BufferSize = 33;
    char buffer[BufferSize];
    size_t m = size % BufferSize;

    MemSize /= BufferSize;
    for (size_t i = 0; i < size; i++)
    {
        memcpy(buffer, a, BufferSize);
        memcpy(a, b, BufferSize);
        memcpy(b, buffer, BufferSize);

        a += BufferSize;
        b += BufferSize;
    }

    memcpy(buffer, a, m);
    memcpy(a, b, m);
    memcpy(b, buffer, m);
}
