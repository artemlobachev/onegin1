#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileWorks.h"

int InitFileStruct(FileStruct *text, const char *FileName)
{
    assert(FileName != NULL);

    /*open 'only-read' file */
    text->ReadFile = fopen(FileName, "rb");
    if (text->ReadFile == nullptr)
    {
        perror("FILE READING ERROR: ");
        return 0;
    }

    /*_stat struct inizilization(getting information about file) */
    if (_stat(FileName, &text->FileInfo) != 0)
    {
        perror("FILE INFO ERROR: ");
        return 0;
    }
    int TextMemorySize = text->FileInfo.st_size;
    
    /*alloc and filling the buffer chars from the text*/
    text->buffer = (char *) calloc(sizeof(char), TextMemorySize);
    if (text->buffer == nullptr)
    {
        perror("ALLOCATION ERROR: ");
        return 0;
    }
    size_t ReadBytes = fread(text->buffer, sizeof(char), TextMemorySize, text->ReadFile);
    if (ReadBytes != TextMemorySize) 
    {
        perror("WRONG! ZERO BYTES READ: ");
        return 0;
    }

    /*alloc and fill array of pointer-on-strings by TextParser*/
    text->NumbStrings = CountNewLines(text->buffer);
    text->pointer = (StringPointers *) calloc(sizeof(StringPointers), text->NumbStrings);
    if (text->pointer == nullptr)
    {
        perror("ALLOCATION ERROR: ");
        return 0;
    }
    TextParser(text->buffer, text->pointer);
    
    return 1;
}

int CountNewLines(char *buffer)
{
    int count = 0;
    
    while (*buffer != '\0')
    {
        if (*buffer == '\n')
        {
            count++;
        }
        buffer++;
    }
    return count;
}

void TextParser(char *text, StringPointers *pointer)
{
    assert(text != nullptr && pointer != nullptr);

    int i = 0, strindex = 0;
    
    pointer[0].StartString = &text[0];
    while (text[i] != '\0' )
    {
        if (text[i] == '\n')
        {
            pointer[strindex].EndString = &text[i - 1];
            text[i] = '\0';
            strindex++;
            if (text[i + 1] != '\0')
                pointer[strindex].StartString = &text[i + 1];
        }
        
        i++;
    }
}

void WriteFile(FileStruct *text, const char *FileName)
{
    text->WriteFile = fopen(FileName, "wb");
    
    for (int i = 0; i < text->NumbStrings; i++)
    {    
        fwrite(text->pointer[i].StartString, sizeof(char), strlen(text->pointer[i].StartString) , text->WriteFile);
        fprintf(text->WriteFile, "\n");
    }
}

void Destructor(FileStruct *text)
{
    free(text->buffer);
    free(text->pointer);
    fclose(text->ReadFile);
    fclose(text->WriteFile);
    
    text->buffer = nullptr;
    text->pointer = nullptr;
    text->ReadFile = nullptr;
    text->WriteFile = nullptr;
}