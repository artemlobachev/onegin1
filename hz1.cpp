#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void BubbleSortForStrings(char *SomeText, const int strings, const int strlen, int *index);
void swap(void *a, void *b, size_t MemSize);
int *FromZeroToN(int *index, int n);
int strcmpAnyRegist(char *word1, char *word2);

int main()
{
    //best way dynamical memory w variable len string
    const int STRINGS = 4;
    const int STRLEN = 32;
    char SomeText[STRINGS][STRLEN] = {"alfred envelope" ,"alfred Aoggins",
                                            "alfred coDSAsgings","alfred DSBwens"};

    int index[STRINGS] = {};
    FromZeroToN(index, STRINGS);

    BubbleSortForStrings(SomeText[0], STRINGS, STRLEN, index);

    for (int i = 0; i < STRINGS; i++)
        puts(SomeText[index[i]]);


}

void BubbleSortForStrings(char *SomeText, const int strings, const int strlen, int *index)
{
    for( int step = 0; step < strings; step++)
        for (int i = step; i < strings - step - 1; i++)
        {
            char *FirstStr = SomeText + strlen * index[i];
            char *SecondStr = SomeText + strlen * index[i+1];

            assert(FirstStr != NULL && SecondStr != NULL);
            assert(FirstStr != SecondStr);

            if (strcmpAnyRegist(FirstStr, SecondStr) > 0)
            {
                assert(&index[i] != NULL && &index[i+1] != NULL);

                swap(&index[i], &index[i+1], sizeof(&index[i]));
            }
        }
}

int *FromZeroToN(int *index, int n)
{
    for (int i = 0; i < n; i++)
        index[i] = i;

    return index;
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
