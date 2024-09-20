#ifndef TEXTSORT_H
#define TEXTSORT_H
#include <stdlib.h>

void swap(void *a, void *b, size_t MemSize);
int SkipNotAlpha(char **str1, char **str2);
int CompareStrings(void *word1, void *word2);
int ReCompareStrings(void *str1, void *str2);
void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (void *, void *) );

#endif