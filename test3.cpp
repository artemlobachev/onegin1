#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char **PtrArr;

    PtrArr = (const char **) calloc(sizeof(char *), 3);
    PtrArr[0] = "hrekkdsadsadsadsa";
    PtrArr[1] = "fdsfd";
    PtrArr[2] = "dassd";
    puts(PtrArr[1]);

}
