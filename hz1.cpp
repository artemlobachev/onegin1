#include <stdio.h>
#include <string.h>
#include <assert.h>

void BubbleSortForStrings(char *SomeText, const int strings, const int strlen, int *index);
void swap(void *a, void *b);
int *FromZeroToN(int *index, int n);

int main()
{
    //best way dynamical memory w variable len string
    const int STRINGS = 4;
    const int STRLEN = 32;
    char SomeText[STRINGS][STRLEN] = {"alfred envelope" ,"alfred aoggins",
                                            "alfred coogings","alfred bwens"};

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
            const char *FirstStr = SomeText + strlen * index[i];
            const char *SecondStr = SomeText + strlen * index[i+1];

            assert(FirstStr != NULL && SecondStr != NULL);
            //UpToLow(FirstStr, SecondStr);

            if (strcmp(FirstStr, SecondStr) > 0)
            {
                assert(&index[i] != NULL && &index[i+1] != NULL);

                swap(&index[i], &index[i+1]);
            }
        }
}

int *FromZeroToN(int *index, int n)
{
    for (int i = 0; i < n; i++)
        index[i] = i;

    return index;
}

//void UpToLow(const char

void swap(void *a, void *b)
{
    assert(a != NULL && b != NULL);

    void c = b;
    *a = *b;
    *b = c;
}
