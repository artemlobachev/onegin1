#ifndef FILEWORKS_H
#define FILEWORKS_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

/** @file
 * @brief Have all function that needed for the works with files(texts)
 */

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

/**
 * @brief Initilization file structure
 * @details get info about his size, how much new lines files have, pointers on start, end
 * @param [out] text - struct with all information about text
 * @param [in] FileName
 * @return 1 - if works well 0 - else
 */
int InitFileStruct(FileStruct *text, const char *FileName);
/**
 * @brief Count new lines("\n")
 * @param [in] buffer - same text that stored in file
 * @return how much is new lines 
 */
int CountNewLines(char *buffer);
/**
 * @brief Get pointers on the start and end of strings and parsing text on a litte strings
 * @param [out] text
 * @param [out] pointer
 */
void TextParser(char *text, StringPointers *pointer);
/**
 * @brief Writing into some file
 * @param [out] text - here stored WriteFile
 * @param [in] FileName
 * @return 1 - if works well 0 - else  
 */
int WriteIntoFile(FileStruct *text, const char *FileName);
/**
 * @brief Destuctor
 * @param text - close and free all allocated and open parameters
 */
void Destructor(FileStruct *text);

#endif