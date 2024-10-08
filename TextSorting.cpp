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

int CompareStringsStart(const void *StringStructure1, const void *StringStructure2)
{
    assert(StringStructure2 != NULL && StringStructure2 != NULL);

    StringPointers structure1 = *(StringPointers *) StringStructure1;
    StringPointers structure2 = *(StringPointers *) StringStructure2;

    char *start1 = structure1.StartString;
    char *start2 = structure2.StartString;

    char *end1 = structure1.EndString;
    char *end2 = structure2.EndString;

    while (*start1 != *end1 || *start2 != *end2)
    { 
        if (isalpha(*start1) && isalpha(*start2))
        {
            char charcmp1 = tolower(*start1);
            char charcmp2 = tolower(*start2);

            if (charcmp1 > charcmp2)
                return 1;
            if (charcmp1 < charcmp2)
                return -1;
            start1++;
            start2++;
        }
        else if (isalpha(*start1) == 0)
            start1++;
        else
            start2++;
    }
    return 0;
}

int CompareStringsEnd(const void *StringStructure1, const void *StringStructure2) 
{
    assert(StringStructure1 != NULL && StringStructure2 != NULL);

    StringPointers structure1 = *(StringPointers *) StringStructure1;
    StringPointers structure2 = *(StringPointers *) StringStructure2;

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

        qsort(array, pivot_index + 1, element_size, comparator);  /*qsort for left elements less then pivot*/
        qsort((char *)array + (pivot_index + 1) * element_size, elements - pivot_index - 1, element_size, comparator); /*qsort for right elements more then pivot*/
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

    /*need for save information about pivot else pivot is change(but he should be const)*/
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