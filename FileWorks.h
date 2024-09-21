#ifndef FILEWORKS_H
#define FILEWORKS_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

struct StringPointers
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
    StringPointers *pointer;
};

int InitFileStruct(FileStruct *text, const char *FileName);
int CountNewLines(char *buffer); // todo
void TextParser(char *text, StringPointers *pointer);
void WriteFile(FileStruct *text, const char *FileName);
void Destructor(FileStruct *text);

#endif