#include <stdio.h>
#include <strings.h>
#include <assert.h>

void swap1(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;    
}

void swap(void *a, void *b, size_t MemorySize)
{
    assert(a != NULL && b != NULL);
    //assert(a != b);

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

int partition(void *arr, int l, int r, size_t size, int (*comparator) (void *, void *))
{
    void *pivot = arr + (int) ( ((r + l) / 2) * size );
    
    //printf("%d ", *(int *)pivot);
    while (l <= r)
    {
        //printf("%d %d ", *(int *)(arr + (int) (size * l)), *(int *) (arr + (int) (size * r)));
        while (comparator(arr + (int) (size * l), pivot) < 0)
            l++;
        //printf("pivot = %d arr[r] = %d\n", *(int *) pivot, *(int *) (arr + (int) (size * r)));
        while (comparator(arr + (int) (size * r), pivot) > 0)
            r--; 
        if (l >= r)
            break;
        swap(arr + (int) (size * r), arr + (int) (size * l), sizeof(int *));
        r--;
        l++;
    }
    return r;
}

int comp(void *a, void *b)
{
    return (*(int *) a - *(int *) b);
}

void qsort(void *arr, int elements, size_t size, int (*comparator) (void *, void *))
{
    if (elements > 1)
    {
        int l = 0;
        int r = elements - 1;
        //printf("%d ", r);
        int pivot_index = partition(arr, l, r, size, comparator);
        printf("%d ", pivot_index);
        //printf("%d ", pivot_index);
        int left_side_elements = pivot_index - l + 1;
        int right_side_elements = elements - left_side_elements;

        qsort(arr, left_side_elements, size, comparator);
        qsort(arr + (int) (left_side_elements * size), right_side_elements, size, comparator);
    }
}

int main()
{
    const int N = 7;
    int l = 0, r = N - 1;
    int arr[N] = {15, 6, 8, 2, 40, 3, 8};
    qsort(arr, N, sizeof(int), comp);
    for (int i = 0; i < N; i++)
        ;//printf("%d ", arr[i]);

}