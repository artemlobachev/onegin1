#ifndef TEXTSORT_H
#define TEXTSORT_H
#include <stdlib.h>

void swap(void *a, void *b, size_t MemSize);
int SkipNotAlpha(char **str1, char **str2);
int CompareStrings(const void *word1, const void *word2);
int ReCompareStrings(const void *str1, const void *str2);
void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (const void *, const void *) );
void qsort1(void *arr, int elements, size_t size, int (*comparator) (const void *, const void *));
int partition(void *arr, int l, int r, size_t size, int (*comparator) (const void *, const void *));

#endif