#ifndef FILEWORKS_H
#define FILEWORKS_H
#include <stdio.h>

/** @file
 * @brief Have all function that needed for the works with files(texts)
 */

struct StringPointers
{
    char *StartString;
    char *EndString;
    int NumbStrings;
    char *buffer;
};

struct TextInfo
{
    char *TextBuffer;
    int NumbStrings;
    StringPointers *TextPointers;
};

/**
 * @brief Initilization file structure
 * @details get info about his size, how much new lines files have, pointers on start, end
 * @param [out] text - struct with all information about text
 * @param [in] FileName
 * @return How much new lines  was read if > 0 works well
 */
int InitTextInfo(TextInfo *text, const char *FileName);
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
void TextParser(char *text, StringPointers *TextPointers);
/**
 * @brief Writing into some file
 * @param [out] text - here stored WriteFile
 * @param [in] FileName
 * @return 1 - if works well 0 - else  
 */
int OneMoreAlpha(char* StartString, char* EndString);
int WriteIntoFile(StringPointers *TextPointers, const char *FileName, int NumbStrings);
/**
 * @brief Destuctor
 * @param text - =free all allocated parameters
 */
void Destructor(TextInfo *text);

#endif