#ifndef FILEWORKS_H
#define FILEWORKS_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
struct FileStructInit
{
    struct _stat FileInfo;

    FILE *ReadFile;
    FILE *WriteFile;
    char *buffer;
    int NumbStrings;
    char **StringPointers;
};

int GetInfoAboutFile(FileStructInit *text, const char *FileName);
int CountNewLines(char *buffer); // todo
void TextParser(char *text, char **StringPointers);
void WriteFile(FileStructInit *text, const char *FileName);
void AllFree (FileStructInit *text);

#endif