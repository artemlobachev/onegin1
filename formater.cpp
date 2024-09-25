#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void swap(void *a, void *b, size_t MemorySize)
{
    assert(a != NULL && b != NULL);
    if (a != b)
    {
        static const size_t BufferSize = 64;
        static char buffer[BufferSize];

        /*parse the parametrs a, b on the little part and recopy them */
        while (MemorySize > BufferSize)
        {
            MemorySize-= BufferSize;
            memcpy(buffer, a, BufferSize);
            memcpy(a, b, BufferSize);
            memcpy(b, buffer, BufferSize);

            a += BufferSize;
            b += BufferSize;
        }

        memcpy(buffer, a, MemorySize);
        memcpy(a, b, MemorySize);
        memcpy(b, buffer, MemorySize);
    }
}

int main(int argc, const char *argv[])
{
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "rb");
        
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);              
        rewind(file);
        
        char *TextBuffer = (char *) calloc(size, sizeof(char));
        char *StartBuf = TextBuffer;

        fread(TextBuffer, sizeof(char), size, file);
        while (*TextBuffer != '\0')
        {
            if (!(isalpha(*TextBuffer) && ispunct(*TextBuffer) && isspace(*TextBuffer)))
                putchar(*TextBuffer);
        
            TextBuffer++;
        }
        while (*StartBuf != '\0')
            putchar(*StartBuf++);
        free(TextBuffer);
    }
}
