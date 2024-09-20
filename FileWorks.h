#ifndef FILEWORKS_H
#define FILEWORKS_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

struct StartEndPointers
{
    char *StartString;
    char *EndString;
};

struct FileStruct
{
    struct _stat FileInfo;
    
    FILE *ReadFile;
    FILE *WriteFile;
    char *buffer;
    int NumbStrings;
    char **StringPointers;
    StartEndPointers *arr;
};

int InitFileStruct(FileStruct *text, const char *FileName);
int CountNewLines(char *buffer); // todo
void TextParser(char *text, char **StringPointers, StartEndPointers *arr);
void WriteFile(FileStruct *text, const char *FileName);
void Destructor(FileStruct *text);

#endif