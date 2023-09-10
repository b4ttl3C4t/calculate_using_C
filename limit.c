#include <stdio.h>
#include <math.h>

void limit_to_zero(double (*)(double));

double f(double x)
{
    return sin(x) / x;
}

int main(void)
{
    limit_to_zero(f);
}

void limit_to_zero(double (*function)(double))
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        printf("%lf \n", function(pow(10, -i)));
    }
}