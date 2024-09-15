#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "TextSorting.h"

void swap(void *a, void *b, size_t MemSize)
{
    assert(a != NULL && b != NULL);
    assert(a != b);

    char *a1 = *(char **) a;
    char *b1 = *(char **) b;
    size_t BufferSize = 32;
    char buffer[BufferSize];   //a = &StringPointers[i]

    for (size_t i = 0; MemSize > BufferSize; i++)
    {
        MemSize-= BufferSize;
        memcpy(buffer, a1, BufferSize);
        memcpy(a1, b1, BufferSize);
        memcpy(b1, buffer, BufferSize);

        a1 += BufferSize;
        b1 += BufferSize;
    }

    memcpy(buffer, a, MemSize);
    memcpy(a, b, MemSize);
    memcpy(b, buffer, MemSize);
}

int strcmpAnyRegist(void *word1, void *word2)
{
    assert(word1 != NULL && word2 != NULL);
    assert(word1 != word2);

    char *str1 = *(char **) word1; // word1 == &StringPointers str1 == указатель на строку
    char *str2 = *(char **) word2;
    while (*str1 != '\0' || *str2 != '\0')
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

    return 0;
}

void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (void *, void *) )
{
    //&arr[i] == &StringPointers[i]
    //arr[i] == StringPointers[i] 
    for( int step = 0; step < elements - 1; step++)
        for (int i = 0; i < elements - step - 1; i++)
        {   
            if (comparator(arr + i * ElemSize, arr + (i + 1) * ElemSize) > 0) // передаем &StringPointers[i]
                swap(arr + i * ElemSize, arr + (i + 1) * ElemSize, ElemSize);
        }
}
