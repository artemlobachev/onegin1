#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "TextSorting.h"

struct WorkWithText
{
    struct _stat FileInfo;

    FILE *ReadFile;
    FILE *WriteFile;
    char *buffer;
    int NumbStrings;
    char **StringPointers;
};

int GetInfoAboutText(WorkWithText *text, const char *FileName);
void TextParser(char *text, char **StringPointers);
void WriteOutFile(WorkWithText *text, const char *FileName);
int CountNL(char *buffer);

int main()
{
    WorkWithText onegin = {0};

    GetInfoAboutText(&onegin, "test.txt");
    BubbleSort(onegin.StringPointers, onegin.NumbStrings, sizeof(char *), strcmpAnyRegist);
    WriteOutFile(&onegin, "testout.txt  ");

    free(onegin.buffer);
    free(onegin.StringPointers);
}

void WriteOutFile(WorkWithText *text, const char *FileName)
{
    text->WriteFile = fopen(FileName, "wb");
    
    for (int i = 0; i < text->NumbStrings; i++)
    {    
        fwrite(text->StringPointers[i], sizeof(char), strlen(text->StringPointers[i]) , text->WriteFile);
        fprintf(text->WriteFile, "\n");
    }
}

int GetInfoAboutText(WorkWithText *text, const char *FileName)
{
    assert(FileName != NULL);

    text->ReadFile = fopen(FileName, "r");

    if (text->ReadFile == NULL)
        perror("FILE ERROR:");

    if (_stat(FileName, &(text->FileInfo )) != 0)   /*_stat struct inizilization(getting information about file) */
        perror("FILE INFO ERROR: ");

    int TextMemSize = text->FileInfo.st_size;
    text->buffer = (char *) calloc(sizeof(char), TextMemSize);

    long ReadBytes = fread(text->buffer, sizeof(char), TextMemSize, text->ReadFile);
    
    if (ReadBytes == 0)
        puts("Something wrong with reading file!");
    
    text->NumbStrings = CountNL(text->buffer);
    text->StringPointers = (char **) calloc(sizeof(char *), text->NumbStrings);
    
    if (text->buffer == NULL || text->StringPointers == NULL)   
        perror("ALLOCATION ERROR: ");

    TextParser(text->buffer, text->StringPointers);
}

void TextParser(char *text, char **StringPointers)
{
    assert(text != NULL && StringPointers != NULL);

    int i = 0, str = 0;
    
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

int CountNL(char *buffer)
{
    int count = 0;
    
    while (*buffer++ != '\0')
    {
        if (*buffer == '\n')
            count++;
    }
    return count;
}

