#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileWorks.h"

int GetInfoAboutFile(FileStructInit *text, const char *FileName)
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
    TextParser(text->buffer, text->StringPointers);
    
    return 1;
}

int CountNewLines(char *buffer)
{
    int count = 0;
    
    while (*buffer != '\0')
    {
        if (*buffer == '\n')
            count++;
        buffer++;
    }
    return count;
}

void TextParser(char *text, char **StringPointers)
{
    assert(text != NULL && StringPointers != NULL);

    int i = 0, str = 0; //
    
    StringPointers[0] = &text[0];
    while (text[i] != '\0' )
    {
        if (text[i] == '\n')
        {
            text[i] = '\0';
            str++;
            StringPointers[str] = &text[i + 1];
        }
        i++;
    }
}

void WriteFile(FileStructInit *text, const char *FileName)
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

void AllFree(FileStructInit *text)
{
    free(text->buffer);
    free(text->StringPointers);
    fclose(text->ReadFile);
    fclose(text->WriteFile);

    text->buffer = nullptr;
    text->StringPointers = nullptr;
    text->ReadFile = nullptr;
    text->WriteFile = nullptr;
}