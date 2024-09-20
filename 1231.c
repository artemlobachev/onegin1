#include <stdio.h>
#include <math.h>

long long factorial(int numb)
{
    int i;
    long long result = 1;
    for (i = 1; i <= numb; i++)
        result *= i;
    return result;
}

void normx(double *x)
{
    if (*x > 0)
        while(*x > 3.14159265)
            *x-= 3.14159265;
    else
        while(*x < -3.14159265)
            *x+= 3.14159265;
}

int main()
{
    double x = 0;

    scanf("%lf", &x);
    normx(&x);
    double sinx = 0.0;
    int chet = 1;
    int i;
    for (i = 1; i <= 10; i = i + 2)
    {
        if (chet % 2 != 0)
            sinx += pow(x, i) / factorial(i);
        else
            sinx -= pow(x, i) / factorial(i);
        chet++;
    }
    printf("%lf\n", sinx);
}