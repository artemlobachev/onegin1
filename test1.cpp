#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void swap (void *a, void *b, size_t MemSize);
int strcmpAnyRegist(char *word1, char *word2);
void BubbleSort(void *arr, size_t elements, size_t MemSize, int (*comparator) (char *, char *));

int main()
{
    char a[3][32] = {"hellsdsaddasdao", "manfdgf", "fdsfgdsfdsfdsa" };
    char b[3][32] = {"dsa23dsaw", "fsagwwr ewqewq", "ewqrqtfgskofsdko" };
    char SomeText[4][32] = {"alfred envelope" ,"alfred aoggins",
                                       "alfred Coogings","alfred DSbwens"};
    FILE *fp = fopen("test.txt", "r");
    char *arr = (char *) calloc(sizeof(char), 70);
    fseek(fp, 0L, SEEK_END);
    int ba = ftell(fp);
    rewind(fp);
    int numb = fread(arr, sizeof(char), ba, fp);
    printf("%d %d\n", numb, ba);

    puts(arr);

    puts(a[0]);
    puts(b[0]);
    swap(a[0], b[0], sizeof(a[0]));
    puts(a[0]);
    puts(b[0]);

}

void swap(void *a, void *b, size_t MemSize)
{
    assert(a != NULL && b != NULL);
    assert(a != b);

    size_t BufferSize = 33;
    char buffer[BufferSize];

    for (size_t i = 0; MemSize > BufferSize; i++)
    {
        MemSize-= BufferSize;
        memcpy(buffer, a, BufferSize);
        memcpy(a, b, BufferSize);
        memcpy(b, buffer, BufferSize);

        a += BufferSize;
        b += BufferSize;
    }

    memcpy(buffer, a, MemSize);
    memcpy(a, b, MemSize);
    memcpy(b, buffer, MemSize);
}

int strcmpAnyRegist(char *word1, char *word2)
{
    assert(word1 != NULL && word2 != NULL);
    assert(word1 != word2);

    while (*word1++ != '\0' && *word2++ != '\0')
    {
        char charcmp1 = tolower(*word1);
        char charcmp2 = tolower(*word2);

        if (charcmp1 > charcmp2)
            return 1;
        if (charcmp1 < charcmp2)
            return -1;
    }

    return 0;
}

void BubbleSort(void *arr, size_t elements, size_t MemSize, int (*comparator) (void *, void *) )
{
    for( int step = 0; step < elements; step++)
        for (int i = step; i < elements - step - 1; i++)
        {
            int AdrStep1 = MemSize * i;
            int AdrStep2 = MemSize * (i + 1);

            if (comparator(arr + AdrStep1, arr + AdrStep2) > 0)
                swap(arr + AdrStep1, arr + AdrStep2, MemSize);
        }
}
