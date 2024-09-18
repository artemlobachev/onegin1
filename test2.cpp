#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "TextSorting.h"
#include "FileWorks.h"

int main(int argc, const char *file[]) 
{
    if (argc == 3)
    {
        WorkWithText text = {0};

        if (GetInfoAboutFile(&text, file[1]))
        {
            BubbleSort(text.StringPointers, text.NumbStrings, sizeof(char *), strcmpAnyRegist);
            WriteFile(&text, file[2]);
            AllFree(&text);
        }
    }
    else
        puts("Wrong! Nothing entered!");
}