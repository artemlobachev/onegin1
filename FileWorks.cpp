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
    text->StringPointers = (char **) calloc(sizeof(char *), text->NumbStrings);
    text->arr = (StartEndPointers *) calloc(sizeof(StartEndPointers), text->NumbStrings);
    if (text->StringPointers == nullptr)
    {
        perror("ALLOCATION ERROR: ");
        return 0;
    }
    TextParser(text->buffer, text->StringPointers, text->arr);
    
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

void TextParser(char *text, char **StringPointers, StartEndPointers *arr)
{
    assert(text != nullptr && StringPointers != nullptr);

    int i = 0, strindex = 0;
    
    StringPointers[0] = &text[0];
    arr->StartString = &text[0];

    while (text[i] != '\0' )
    {
        if (text[i] == '\n')
        {
            arr->EndString = &text[i - 1];
            text[i] = '\0';
            strindex++;
            StringPointers[strindex] = &text[i + 1];
            arr->StartString = &text[i + 1];
        }
        i++;
    }
}

void WriteFile(FileStruct *text, const char *FileName)
{
    text->WriteFile = fopen(FileName, "wb");
    
    for (int i = 0; i < text->NumbStrings; i++)
    {    
        fwrite(text->StringPointers[i], sizeof(char), strlen(text->StringPointers[i]) , text->WriteFile);
        fprintf(text->WriteFile, "\n");
    }
    
    fclose(text->WriteFile);
    text->WriteFile = nullptr;
}

void Destructor(FileStruct *text)
{
    free(text->buffer);
    free(text->StringPointers); //???
    fclose(text->ReadFile);
    fclose(text->WriteFile);
    
    text->buffer = nullptr;
    text->StringPointers = nullptr;
    text->ReadFile = nullptr;
    text->WriteFile = nullptr;
}