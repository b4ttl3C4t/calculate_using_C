#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LOWER -10000000000000
#define UPPER  10000000000000

static clock_t begin, end;

void limit_to_zero(double (*)(double));
//The iterative bisection method.
double iter_bisect_method   (double);
double Newton_method        (double);

void   first_differentiation            (double (double));
double first_right_derivative           (double, double, double (double));
double first_symmetric_derivative       (double, double, double (double));
double first_five_point_derivative      (double, double, double (double));

void   second_differentiation           (double (double));
double second_right_derivative          (double, double, double (double));
double second_symmetric_derivative      (double, double, double (double));
double second_five_point_derivative     (double, double, double (double));

void   recursive_differentiation        (double (double));
double recursive_right_derivative       (unsigned int, double, double, double (double));
double recursive_symmetric_derivative   (unsigned int, double, double, double (double));
double recursive_five_point_derivative  (unsigned int, double, double, double (double));

void   numerical_integration        (double (double));
double definite_integral_right      (double, double, double, double (double));
double definite_integral_trapezium  (double, double, double, double (double));
double definite_integral_Simpson    (double, double, double (double));

double f(double x)
{
    return cos(x)/x + x/cos(x);
}

int main(void)
{begin = clock();

    recursive_differentiation(f);

end = clock();
printf("\n|%lf|\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

/*The iterative version of bisection method
 *to find the approximation of the given root
 *base on the mean value therom.
 */
void limit_to_zero(double (*function)(double))
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        printf("%lf \n", function(pow(10, -i)));
    }
}

double iter_bisect_method(double target)
{
    double lower  = LOWER;
    double upper  = UPPER;
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

double Newton_method(double target)
{
    
}

void first_differentiation(double f(double))
{
    double x, h;

    printf("\n%s", "> Enter the x :");
    scanf("%lf", &x);
    getchar();

    printf("\n%s", "> Enter the h :");
    scanf("%lf", &h);
    getchar();

    printf("first_right_derivative \tapproach to %lf is %lf\n", 
        x, first_right_derivative(x, h, f));

    printf("first_symmetric_derivative \tapproach to %lf is %lf\n", 
        x, first_symmetric_derivative(x, h, f));
    
    printf("first_five_point_derivative \tapproach to %lf is %lf\n", 
        x, first_five_point_derivative(x, h, f));
}

double first_right_derivative(double x, double h, double f(double))
{
    return (f(x + h) - f(x)) / h;
}

double first_symmetric_derivative(double x, double h, double f(double))
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

double first_five_point_derivative(double x, double h, double f(double))
{
    return (f(x - 2*h) + 8 * f(x + h) - 8 * f(x - h) - f(x + 2*h)) / (12 * h);
}

void second_differentiation(double f(double))
{
    double x, h;

    printf("\n%s", "> Enter the x :");
    scanf("%lf", &x);
    getchar();

    printf("\n%s", "> Enter the h :");
    scanf("%lf", &h);
    getchar();

    printf("second_right_derivative \tapproach to %lf is %lf\n", 
        x, second_right_derivative(x, h, f));

    printf("second_symmetric_derivative \tapproach to %lf is %lf\n", 
        x, second_symmetric_derivative(x, h, f));
    
    printf("second_five_point_derivative \tapproach to %lf is %lf\n", 
        x, second_five_point_derivative(x, h, f));
}

double second_right_derivative(double x, double h, double f(double))
{
    return (first_right_derivative(x + h, h, f) - first_right_derivative(x, h, f)) / h;
}

double second_symmetric_derivative(double x, double h, double f(double))
{
    return (first_symmetric_derivative(x + h, h, f) - first_symmetric_derivative(x - h, h, f)) / (2 * h);
}

double second_five_point_derivative(double x, double h, double f(double))
{
    return (first_five_point_derivative(x + h, h, f) - first_five_point_derivative(x, h, f)) / h;
}

void recursive_differentiation(double f(double))
{
    unsigned int i;
    double x, h, n;

    printf("\n%s", "> Enter the x :");
    scanf("%lf", &x);
    getchar();

    printf("\n%s", "> Enter the h :");
    scanf("%lf", &h);
    getchar();
    
    printf("\n%s", "> Enter the n :");
    scanf("%lf", &n);
    getchar();

    for(i = 0; i <= n; ++i)
        printf("recursive_right_derivative f_%u(x) \tapproach to %lf is %lf\n", 
            i, x, recursive_right_derivative(i, x, h, f));

    for(i = 0; i <= n; ++i)
        printf("recursive_symmetric_derivative f_%u(x) \tapproach to %lf is %lf\n", 
            i, x, recursive_symmetric_derivative(i, x, h, f));
            
    for(i = 0; i <= n; ++i) 
        printf("recursive_five_point_derivative f_%u(x) \tapproach to %lf is %lf\n",
            i, x, recursive_five_point_derivative(i, x, h, f));
}

double recursive_right_derivative(unsigned int n, double x, double h, double f(double))
{
    if(n == 0)
        return f(x);
    if(n == 1)
        return first_right_derivative(x, h, f);
    else
        return (recursive_right_derivative(n-1, x + h, h, f) - recursive_right_derivative(n-1, x, h, f)) / h;
}

double recursive_symmetric_derivative(unsigned int n, double x, double h, double f(double))
{
    if(n == 0)
        return f(x);
    if(n == 1)
        return first_symmetric_derivative(x, h, f);
    else
        return (recursive_symmetric_derivative(n-1, x + h, h, f) - recursive_symmetric_derivative(n-1, x - h, h, f)) / (2 * h);
}

double recursive_five_point_derivative(unsigned int n, double x, double h, double f(double))
{
    if(n == 0)
        return f(x);
    if(n == 1)
        return first_five_point_derivative(x, h, f);
    else
        return (recursive_five_point_derivative(n-1, x - 2*h, h, f) + 8 * recursive_five_point_derivative(n-1, x + h, h, f) 
                - 8 * recursive_five_point_derivative(n-1, x - h, h, f) - recursive_five_point_derivative(n-1, x + 2*h, h, f)) / (12 * h);
}

void numerical_integration(double func(double))
{
    double lower, upper, partition;

    printf("\n%s", "> Enter the lower and upper :");
    scanf("%lf%lf", &lower, &upper);
    getchar();

    printf("\n%s", "> Enter the partition :");
    scanf("%lf", &partition);
    getchar();

    if(partition < 1)
    {
        fprintf(stderr, "\n%s", "> The partition shouldn't be less than 1.");
        return ;
    }

    printf("definite_integral_right with domain from %lf to %lf is %lf\n", 
        lower, upper, definite_integral_right(lower, upper, partition, func));

    printf("definite_integral_trapezium with domain from %lf to %lf is %lf\n", 
        lower, upper, definite_integral_trapezium(lower, upper, partition, func));
    
    printf("definite_integral_Simpson with domain from %lf to %lf is %lf\n", 
        lower, upper, definite_integral_Simpson(lower, upper, func));
}

//Calculating definite integral by right side height.
double definite_integral_right(double lower, double upper, double partition, double func(double))
{
    double summation = 0.0;
    double height    = 0.0;
    double width     = (upper - lower) / partition;
    unsigned int i;

    for(i = 1; i <= partition; ++i)
    {
        /*Obtaining the approximate summation of func (integral from lower to upper)
         *by calculating the height multiple the width step by step.
         */
        height = func(lower + i * width);
        summation += height;
    }

    //You can move out the multiplication of width by distributive property.
    summation *= width;

    return summation;
}

//Calculating definite integral by trapezium.
double definite_integral_trapezium(double lower, double upper, double partition, double func(double))
{
    double summation = 0.0;
    double height    = 0.0;
    double width     = (upper - lower) / partition;
    unsigned int i;

    summation += func(lower) / 2;
    for(i = 1; i < partition; ++i)
    {
        height = func(lower + i * width);
        summation += height;
    }
    summation += func(upper) / 2;

    //You can move out the multiplication of width by distributive property.
    summation *= width;

    return summation;
}

/*Calculating definite integral by curse,
 *and you don't have to get the summation by split and input the partiton.
 */
double definite_integral_Simpson(double lower, double upper, double func(double))
{
    double summation = 0.0;

    summation += func(lower);
    summation += 4 * func((lower + upper) / 2);
    summation += func(upper);

    //You can move out the multiplication of width by distributive property.
    summation *= (upper - lower) / 6;

    return summation;
}