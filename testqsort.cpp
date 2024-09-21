#include <stdio.h>
#include <strings.h>
#include <assert.h>

void swap(void *a, void *b, size_t MemorySize)
{
    assert(a != NULL && b != NULL);
    if (a != b)
    {
        static const size_t BufferSize = 32;
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
    else
        puts("swap not works: same address");
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
            pivot = char_array + right_index * element_size;
        
        swap(char_array + element_size * right_index, char_array + element_size * left_index, element_size);
        
        right_index--;
        left_index++;
    }
    return right_index;
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

int comp(const void *a, const void *b)
{
    return (*(int *) a - *(int *) b);
}


int main()
{
    const int N = 7;
    int l = 0, r = N - 1;
    int arr[N] = {15, 6, 8, 2, 40, 3, 8};
    qsort1(arr, N, sizeof(int), comp);
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);

}