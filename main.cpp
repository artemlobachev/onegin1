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
        FileStruct Text = {0};

        if (InitFileStruct(&Text, file[1]))
        {
            BubbleSort(Text.StringPointers, Text.NumbStrings, sizeof(char *), CompareStrings);
            WriteFile(&Text, file[2]);
            Destructor(&Text);
        }
    }
    else
        puts("Wrong! Files not entered!");
}