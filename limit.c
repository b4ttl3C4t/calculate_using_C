#include "limit.h"

#define LOWER           -10000000000000
#define UPPER           10000000000000
#define H_APPROACH_0    0.000001

static clock_t begin, end;
static inline uint64_t factorial(uint32_t n);
static inline uint64_t combination(uint32_t, uint32_t);
static inline uint64_t permutation(uint32_t, uint32_t);

double f(double x)
{
    return sin(x);
}

int32_t main(void)
{begin = clock();

    iterative_differentiation(f);
    recursive_differentiation(f);
    /*
    printf("%lf", f(3.155));
    //*/

end = clock();
printf("\n|%lf|\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

/*The iterative version of bisection method
 *to find the approximation of the given root
 *base on the mean value therom.
 */
void limit_to_zero(double (*function)(double))
{
    int32_t i;

    for(i = 0; i < 10; ++i)
    {
        printf("%lf \n", function(pow(10, -i)));
    }
}

double iterative_bisect_method(double target)
{
    double lower  = LOWER;
    double upper  = UPPER;
    double middle = (upper + lower) / 2;
    
    uint32_t i;    
    
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

//find the root (f(x) = 0).
double Newton_method(double initial_value, double f(double))
{
    double x_n1, x_n0;
    x_n1 = initial_value;

    do
    {
        x_n0 = x_n1;
        x_n1 = x_n0 - (f(x_n0) / first_right_derivative(x_n0, H_APPROACH_0, f));
    }while(Newton_stopping_criteria(x_n1, x_n0, f(x_n0), H_APPROACH_0));

    return x_n1;
}

inline int8_t Newton_stopping_criteria(double x_n1, double x_n0, double f_of_x, double h)
{
    static double x;
    static double y;

    x = fabs(x_n0 - x_n1);
    y = fabs(f_of_x);
   
    if(x < h)       //The nicety between x_n1 and x_n0 is less than h.
        return 0;
    else
        return 1;
    
    if(y < h)       //The nicety of the absolute value of f(x) is less than h.
        return 0;
    else
        return 1;

    if(x*y < h)     //The triangle area ((x*y)/2 ~= x*y) of x and y is less than h.
        return 0;
    else
        return 1;

    if(pow(y*y - x*x, 0.5) < h)     //The length of the secant (((y*y - x*x)^(1/2)) ~= (y*y - x*x)) is less than h.
        return 0;
    else
        return 1;
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

inline double first_right_derivative(double x, double h, double f(double))
{
    return (f(x + h) - f(x)) / h;
}

inline double first_symmetric_derivative(double x, double h, double f(double))
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

inline double first_five_point_derivative(double x, double h, double f(double))
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

inline double second_right_derivative(double x, double h, double f(double))
{
    return (first_right_derivative(x + h, h, f) - first_right_derivative(x, h, f)) / h;
}

inline double second_symmetric_derivative(double x, double h, double f(double))
{
    return (first_symmetric_derivative(x + h, h, f) - first_symmetric_derivative(x - h, h, f)) / (2 * h);
}

inline double second_five_point_derivative(double x, double h, double f(double))
{
    return (first_five_point_derivative(x - 2*h, h, f) + 8 * first_five_point_derivative(x + h, h, f)
            - 8 * first_five_point_derivative(x - h, h, f) - first_five_point_derivative(x + 2*h, h, f)) / (12 * h);
}

void iterative_differentiation(double f(double))
{
    uint32_t i, n;
    double x, h;
    double result = 0;

    printf("\n%s", "> Enter the x :");
    scanf("%lf", &x);
    getchar();

    printf("\n%s", "> Enter the h :");
    scanf("%lf", &h);
    getchar();
    
    printf("\n%s", "> Enter the n :");
    scanf("%u", &n);
    getchar();

    if(n == 0)
    {
        printf("iterative_differentiation f_%u(x) \tapproach to %lf is %lf\n", n, x, f(x));
        return;
    }

    for(i = 0; i <= n; ++i)
    {
        result += pow(-1, i) * combination(n, i) * f(x + (n-i)*h);
    }
    result /= pow(h, n);

    printf("iterative_differentiation f_%u(x) \tapproach to %lf is %lf\n", n, x, result);
    return;
}

//Be cautious about whether h is less than the precise limit.
void recursive_differentiation(double f(double))
{
    uint32_t i, n;
    double x, h;

    printf("\n%s", "> Enter the x :");
    scanf("%lf", &x);
    getchar();

    printf("\n%s", "> Enter the h :");
    scanf("%lf", &h);
    getchar();
    
    printf("\n%s", "> Enter the n :");
    scanf("%u", &n);
    getchar();

    printf("%c", '\n');
    for(i = 0; i <= n; ++i)
        printf("recursive_right_derivative f_%-2u(x) \tapproach to %lf is %+lf\n", 
            i, x, recursive_right_derivative(i, x, h, f));
    
    printf("%c", '\n');
    for(i = 0; i <= n; ++i)
        printf("recursive_symmetric_derivative f_%-2u(x) \tapproach to %lf is %+lf\n", 
            i, x, recursive_symmetric_derivative(i, x, h, f));
    
    printf("%c", '\n');
    for(i = 0; i <= n; ++i) 
        printf("recursive_five_point_derivative f_%-2u(x) \tapproach to %lf is %+lf\n",
            i, x, recursive_five_point_derivative(i, x, h, f));
}

double recursive_right_derivative(uint8_t n, double x, double h, double f(double))
{
    if(n == 0)
        return f(x);
    if(n == 1)
        return first_right_derivative(x, h, f);
    else
        return (recursive_right_derivative(n-1, x + h, h, f) - recursive_right_derivative(n-1, x, h, f)) / h;
}

double recursive_symmetric_derivative(uint8_t n, double x, double h, double f(double))
{
    if(n == 0)
        return f(x);
    if(n == 1)
        return first_symmetric_derivative(x, h, f);
    else
        return (recursive_symmetric_derivative(n-1, x + h, h, f) - recursive_symmetric_derivative(n-1, x - h, h, f)) / (2 * h);
}

double recursive_five_point_derivative(uint8_t n, double x, double h, double f(double))
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
    uint32_t i;

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
    uint32_t i;

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





//----------------------------Internal function--------------------------:
static inline uint64_t factorial(uint32_t n)
{
    static uint64_t result, i;

    if(n == 0 || n == 1)
    {
        return 1;
    }

    result = 1;
    for(i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}


static inline uint64_t permutation(uint32_t n, uint32_t m)
{
    static uint64_t result, i;
    
    result = 1;
    for(i = 1; i <= m; ++i)
    {
        result *= n - i + 1;
    }

    return result;
}

static inline uint64_t combination(uint32_t n, uint32_t m)
{
    static uint64_t result, i;
    
    result = 1;
    for(i = 1; i <= m; ++i)
    {
        result = (result * (n - i + 1)) / i;    //You should not write like "result *= (n - i + 1) / i;", or it will get wrong.
    }

    return result;
}