#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#include <sys/stat.h>

#include "FileWorks.h"


int InitTextInfo(TextInfo *text, const char *FileName)
{
    assert(FileName != NULL);

    /*open 'only-read' file */
    FILE *ReadFile = fopen(FileName, "rb");
    if (ReadFile == nullptr)
    {
        perror("FILE OPENING ERROR: ");
        return 0;
    }

    /*_stat struct inizilization(getting information about file size) */
    struct _stat FileInfo = {0}; 
    
    if (_stat(FileName, &FileInfo) != 0)
    {
        perror("FILE INFO ERROR: ");
        return 0;
    }
    int TextMemorySize = FileInfo.st_size;
    
    /*calloc and filling the buffer formated text*/
    text->TextBuffer = (char *) calloc(TextMemorySize, sizeof(char));

    if (text->TextBuffer == nullptr)
    {
        perror("ALLOCATION ERROR: ");
        return 0;
    }
    size_t ReadBytes = fread(text->TextBuffer, sizeof(char), TextMemorySize, ReadFile);
    if (ReadBytes != TextMemorySize) 
    {
        perror("ERROR READING: ");
        return 0;
    }

    /*alloc and fill array of pointer-on-strings by TextParser*/
    text->NumbStrings = CountNewLines(text->TextBuffer);
    text->TextPointers = (StringPointers *) calloc(text->NumbStrings, sizeof(StringPointers));
    if (text->TextPointers == nullptr)
    {
        perror("ALLOCATION ERROR: ");
        return 0;
    }
    TextParser(text->TextBuffer, text->TextPointers);

    fclose(ReadFile);
    ReadFile = nullptr;

    return 1;
}  

int CountNewLines(char *TextBuffer)
{
    assert(TextBuffer != nullptr);

    int count = 0;
    
    while (*TextBuffer != '\0')
    {
        if (*TextBuffer == '\n') 
            count++;

        TextBuffer++;
    }
    
    return count;
}


void TextParser(char *text, StringPointers *TextPointers)
{
    assert(text != nullptr && TextPointers != nullptr);

    int i = 0, strindex = 0;
    
    TextPointers[0].StartString = &text[0];
    while (text[i] != '\0' )
    {
        if (text[i] == '\n')
        {
            TextPointers[strindex].EndString = &text[i - 1];
            text[i] = '\0';
            strindex++;
            if (text[i + 1] != '\0')        /*else segmentation fault*/
                TextPointers[strindex].StartString = &text[i + 1];
        }
        i++;
    }
}

int WriteIntoFile(StringPointers *TextPointers, const char *FileName, int NumbStrings)
{
    /*Open file when should stored sorted text*/
    FILE *WriteFile = fopen(FileName, "wb");
    if (WriteFile == nullptr)
    {
        perror("WRITE FILE ERROR: ");
        return 0;
    }

    /*Write in file*/
    for (int i = 0; i < NumbStrings; i++)
    {    
        char *StartString = TextPointers[i].StartString;
        char *EndString = TextPointers[i].EndString;
        if(OneMoreAlpha(StartString, EndString))
        {
            if(fwrite(StartString, sizeof(char), strlen(StartString) , WriteFile) == strlen(StartString))
                fprintf(WriteFile, "\n");
            else
            {
                perror("ERROR WRITE FILE: ");
                return 0;
            }
        }
    }
    
    fclose(WriteFile);
    WriteFile = nullptr;

    return 1;
}

int OneMoreAlpha(char* StartString, char* EndString)
{
    while (*StartString != *EndString)
    {
        if (isalpha(*StartString))
            return 1;
        StartString++;
    }
    return 0;
}
void Destructor(TextInfo *text)
{
    assert(text != nullptr);

    free(text->TextBuffer);
    free(text->TextPointers);
    
    text->TextBuffer = nullptr;
    text->TextPointers = nullptr;
}