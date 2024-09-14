#ifndef TEXTSORT_H
#include <stdlib.h>
#define TEXTSORT_H

void swap(void *a, void *b, size_t MemSize);
void swap1(void *a, void *b);
int strcmpAnyRegist(void *word1, void *word2);
void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (void *, void *) );

#endif