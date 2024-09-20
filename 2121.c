#include <stdio.h>

int main()
{
    int x = 0;
    int flag = 1;
    int i = 0;
    int k = 0;
    scanf("%d %d", x, k);
    if (x == 1 && k == 1)
        printf("YES");
    while(x / k != 1)
    {   
        if (x % k == 0)
        {    
            i++;
            x /= 3;
        }
        else
        {
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("YES");
    else
        printf("NO");
}