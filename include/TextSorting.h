#ifndef TEXTSORT_H
#define TEXTSORT_H
#include <stdlib.h>

/** @file
 * @brief Have all function that needed for the sorting text
 */


/** 
 * @brief Swaps any input parametrs
 * @details Create a char buffer with fix size, recopy by the while
 * @param [in] a
 * @param [in] b
 * @param [in] MemorySize - the size of element
 */
void swap(void *a, void *b, size_t MemorySize);
/**
 * @brief Comparing strings by them starts
 * @details Comparing letters from the start strings, skips not-letter symbols
 * @param [in] string1
 * @param [in] string2
 * @return 1 - string1 > string2 0 - else
 */
int CompareStringsStart(const void *string1, const void *string2);
/**
 * @brief Comparing strings by them ends
 * @details Comparing last letters by the rules of alphabet(from a to z), sometimes getting rhyme, skips not-letter symbols
 * @param [in] struct1 - First structure that have pointers on the end of first string
 * @param [in] struct2 - Second structure that have pointers on the end of second string
 * @return 1 - Last letters first string > Last letters second string 0 - else
 */
int CompareStringsEnd(const void *struct1, const void *struct2);
/**
 * @brief Bubble sort
 * @param [in, out] arr - array 
 * @param [in] elements - how much elements in array
 * @param [in] ElemSize - the size of one elements of the array
 * @param [in] comparator
 */
void BubbleSort(void *arr, size_t elements, size_t ElemSize, int (*comparator) (const void *, const void *));
/**
 * @brief Recursive quick sort
 * @param [in, out] array
 * @param [in] elements
 * @param [in] element_size
 * @param [in] comparator
 */
void qsort1(void *array, int elements, size_t element_size, int (*comparator) (const void *, const void *));
/**
 * @brief Parted array
 * @details Get middle element(pivot) on the left side elements that < pivot on the right side elements that > pivot. After we get two arrays
 * @param [in, out] array
 * @param [in] left_index
 * @param [in] right_index
 * @param [in] element_size
 * @param [in] comparator
 */
int partition(void *array, int left_index, int right_index, size_t element_size, int (*comparator) (const void *, const void *));

#endif