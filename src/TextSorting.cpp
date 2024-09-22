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
    if (a != b)
    {
        static const size_t BufferSize = 64;
        char buffer[BufferSize];

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

int CompareStringsStart(const void *word1, const void *word2)
{
    assert(word1 != NULL && word2 != NULL);

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
        else if (isalpha(*str1) == 0)
            str1++;
        else
            str2++;
    }
    return 0;
}

int CompareStringsEnd(const void *str1, const void *str2) //str1 = &structure str2 = &structure +1
{
    assert(str1 != NULL && str2 != NULL);

    StringPointers structure1 = *(StringPointers *) str1;
    StringPointers structure2 = *(StringPointers *) str2;

    char *start1 = structure1.StartString;
    char *start2 = structure2.StartString;

    char *end1 = structure1.EndString;
    char *end2 = structure2.EndString;

    while (end1 != start1 || end2 != start2)
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
        else if (isalpha(*end1) == 0)
            end1--;
        else
            end2--;
    }
    return 0;
}

void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (const void *, const void *) )
{
    for (int step = 0; step < elements - 1; step++)
        for (int i = 0; i < elements - step - 1; i++)   //arr = &pointer[0]
        {   
            if (comparator(arr + i * ElemSize, arr + (i + 1) * ElemSize) > 0) 
                swap(arr + i * ElemSize, arr + (i + 1) * ElemSize, ElemSize);
        }
}

void qsort1(void *array, int elements, size_t element_size, int (*comparator) (const void *, const void *))
{
    if (elements > 1)
    {
        int left_index = 0;
        int right_index = elements - 1;

        int pivot_index = partition(array, left_index, right_index, element_size, comparator);

        qsort1(array, pivot_index + 1, element_size, comparator);  /*qsort for left elements less then pivot*/
        qsort1((char *)array + (pivot_index + 1) * element_size, elements - pivot_index - 1, element_size, comparator); /*qsort for right elements more then pivot*/
    }
}

int partition(void *array, int left_index, int right_index, size_t element_size, int (*comparator) (const void *, const void *))
{
    int middle_index = (right_index + left_index) / 2;   /*search middle index*/
    char *char_array = (char *)array;
    
    void *pivot = char_array + middle_index * element_size; /*pivot == middle element of array*/
    while (left_index <= right_index)
    {
        while (comparator(char_array + element_size * left_index, pivot) < 0)
            left_index++;
        
        while (comparator(char_array + element_size * right_index, pivot) > 0)
            right_index--; 
        
        if (left_index >= right_index)
            break;

        if (pivot == char_array + right_index * element_size)
            pivot = char_array + left_index * element_size;
        
        else if (pivot == char_array + left_index * element_size)
            pivot = char_array + right_index *element_size;
        
        swap(char_array + element_size * right_index, char_array + element_size * left_index, element_size);
        
        right_index--;
        left_index++;
    }
    return right_index;
}