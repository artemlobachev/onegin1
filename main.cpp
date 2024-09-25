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
        TextInfo text = {0};
        
        if (InitTextInfo(&text, file[1]))
        {           
#ifdef END
            qsort(text.TextPointers, text.NumbStrings, sizeof(StringPointers), CompareStringsEnd); /* need flag END*/
#else
            qsort(text.TextPointers, text.NumbStrings, sizeof(StringPointers), CompareStringsEnd);
#endif   
            WriteIntoFile(text.TextPointers, file[2], text.NumbStrings);
        }
        Destructor(&text);
    }
    
    else
    {
        puts("Wrong! Need 2 files ");
        puts("First File: Input");
        puts("Second File: Output");
    }    
}