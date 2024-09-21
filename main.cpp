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
        FileStruct text = {0};

        if (InitFileStruct(&text, file[1]))
        {           
            qsort1(text.pointer, text.NumbStrings, sizeof(StringPointers), CompareStringsEnd);
            //BubbleSort(text.pointer, text.NumbStrings, sizeof(StringPointers), CompareStringsStart);
            WriteIntoFile(&text, file[2]);
        }
        Destructor(&text);
    }
    else
        puts("Wrong! Files not entered!");
}