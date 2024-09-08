#include <stdio.h>
#include <string.h>

void BubbleSortForStrings(char *SomeText, const int STRINGS, const int STRLEN, int *index);
void swapC(int *a, int *b);
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

void BubbleSortForStrings(char *SomeText, const int STRINGS, const int STRLEN, int *index)
{
    for( int step = 0; step < STRINGS; step++)
        for (int i = step; i < STRINGS - step - 1; i++)
        {
            const char *FirstStr = SomeText + STRLEN * index[i];
            const char *SecondStr = SomeText + STRLEN * index[i+1];

            assert(FirstStr != NULL && SecondStr != NULL);
            //UpToLow(FirstStr, SecondStr);

            if (strcmp(FirstStr, SecondStr) > 0)
            {
                assert(&index[i] != NULL && &index[i+1] != NULL);

                swapC(&index[i], &index[i+1]);
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

void swapC(int *a, int *b)
{
    assert(a != NULL && b != NULL);

    int c = *a;
    *a = *b;
    *b = c;
}
