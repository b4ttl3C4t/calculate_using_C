#include <stdio.h>
#include <math.h>

#define LOWER -10000000000000
#define UPPER  10000000000000

void limit_to_zero(double (*)(double));
//The iterative bisection method.
double iter_bisect_method        (double upper, double lower, double target);
//The iterative digit-by-digit calculation..
double iter_digit_calculation    (double upper, double lower, double target);
//The recursive bisection method.
double recu_bisect_method        (double upper, double lower, double target);
//The recursive digit-by-digit calculation.
double recu_digit_calculation    (double upper, double lower, double target);


double f(double x)
{
    return sin(x) / x;
}

int main(void)
{
    double target;
    scanf("%lf", &target);
    
    double result = iter_bisect_method(LOWER, UPPER, target);
    printf("%lf", result);
}

void limit_to_zero(double (*function)(double))
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        printf("%lf \n", function(pow(10, -i)));
    }
}

double iter_bisect_method(double lower_limit, double upper_limit, double target)
{
    double lower  = lower_limit;
    double upper  = upper_limit;
    double middle = (upper + lower) / 2;
    
    unsigned int i;    
    
    //Finding the by mean value theorm.
    for (i = 0; i < 100; ++i)
    {
        if (pow(lower, 2) < target && target < pow(middle, 2))
        {
            upper = middle;
        }
        if (pow(middle, 2) < target && target < pow(upper, 2))
        {
            lower = middle;
        }
        middle = (upper + lower) / 2;
    }
    
    return middle;
}