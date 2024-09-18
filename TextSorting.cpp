#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "TextSorting.h"

void swap(void *a, void *b, size_t MemorySize)
{
    assert(a != NULL && b != NULL);
    //assert(a != b);  IF

    char *a1 = *(char **) a;
    char *b1 = *(char **) b;
    static const size_t BufferSize = 32;
    char buffer[BufferSize];

    for (size_t i = 0; MemorySize > BufferSize; i++)
    {
        MemorySize-= BufferSize;
        memcpy(buffer, a1, BufferSize);
        memcpy(a1, b1, BufferSize);
        memcpy(b1, buffer, BufferSize);

        a1 += BufferSize;
        b1 += BufferSize;
    }

    memcpy(buffer, a, MemorySize);
    memcpy(a, b, MemorySize);
    memcpy(b, buffer, MemorySize);
}

int CompareStrings(void *word1, void *word2)
{
    assert(word1 != NULL && word2 != NULL);
    // assert(word1 != word2);

    char *str1 = *(char **) word1;
    char *str2 = *(char **) word2;
    while (*str1 != '\0' || *str2 != '\0')
    { 
        if (SkipNotAlpha(str1, str2))
        {
            char charcmp1 = tolower(*str1);
            char charcmp2 = tolower(*str2);

            if (charcmp1 > charcmp2)
                return 1;
            if (charcmp1 < charcmp2)
                return -1;
            str1++;
            str2++;
        }
    }

    return 0;
}

int SkipNotAlpha(char *str1, char *str2)
{
    if (isalpha(*str1) == 0)
    {
        str1++;
        return 0;
    }
    if (isalpha(*str2) == 0)
    {    
        str2++;
        return 0;
    }
    return 1;
}

void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (void *, void *) )
{
    for (int step = 0; step < elements - 1; step++)
        for (int i = 0; i < elements - step - 1; i++)
        {   
            if (comparator(arr + i * ElemSize, arr + (i + 1) * ElemSize) > 0) 
                swap(arr + i * ElemSize, arr + (i + 1) * ElemSize, ElemSize);
        }
}
