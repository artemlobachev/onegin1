#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct WorkWithText
{
    struct _stat FileInfo;

    FILE *ReadFile;
    FILE *WriteFile;
    char *buffer;
    char *StringPointers[];

};

int GetInfoAboutText(WorkWithText *text, const char *FileName);
void TextParser(char *text, char *StringPointers[]);

int main()
{
    WorkWithText onegin = {0};

    GetInfoAboutText(&onegin, "InputOnegin.txt");
    //BubbleSort();
    //WriteOutFile();

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
    
    if (text->buffer == NULL)   
        perror("ALLOCATION ERROR: ");
    
    long ReadBytes = fread(text->buffer, sizeof(char), TextMemSize, text->ReadFile);

    if (ReadBytes == 0)
        puts("Something wrong with reading file!");

    TextParser(text->buffer, text->StringPointers);
}

void TextParser(char *text, char *StringPointers[])
{
    int i = 0, str = 0;
    
    StringPointers[0] = &text[0];
    while (text[i] != '\0' )
    {
        if (text[i] == '\n')
        {
            text[i] = '\0';
            StringPointers[str] = &text[i + 1];
        }
        i++;
    }
}
