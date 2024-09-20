#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "TextSorting.h"
#include "FileWorks.h"

void swap(void *a, void *b, size_t MemorySize)
{
    assert(a != NULL && b != NULL);
    //assert(a != b);  IF

    //char *a1 = *(char **) a;
    //char *b1 = *(char **) b;
    static const size_t BufferSize = 64;
    char buffer[BufferSize];

    for (size_t i = 0; MemorySize > BufferSize; i++)
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

//int ReverseCompareStrings(void *w)

int CompareStrings(void *word1, void *word2)
{
    assert(word1 != NULL && word2 != NULL);
    // assert(word1 != word2);

    char *str1 = *(char **) word1;
    char *str2 = *(char **) word2;
    while (*str1 != '\0' || *str2 != '\0')
    { 
        if (isalpha(*str1) && isalpha(*str2))
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
        else if (isalpha(*str1) != 1)
            str1++;
        else
            str2++;
    }
    return 0;
}

int ReCompareStrings(void *str1, void *str2) //str1 = &structure str2 = &structure +1
{
    assert(str1 != NULL && str2 != NULL);

    StartEndPointers structure1 = *(StartEndPointers *) str1;
    StartEndPointers structure2 = *(StartEndPointers *) str2;

    char *start1 = structure1.StartString;
    char *start2 = structure2.StartString;

    char *end1 = structure1.EndString;
    char *end2 = structure2.EndString;

    while (start1 != end1 || start2 != end2)
    {
        if (isalpha(*end1) && isalpha(*end2))
        {
            char charcmp1 = tolower(*end1);
            char charcmp2 = tolower(*end2);

            if (charcmp1 > charcmp2)
                return 1;
            if (charcmp1 < charcmp2)
                return -1;
            end1--;
            end2--;
        }
        else if (isalpha(*end1) != 1)
            end1--;
        else
            end2--;
    }
    return 0;
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
