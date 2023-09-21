#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double definite_integral_right(double, double, double, double (double));
double definite_integral_trapezium(double, double, double, double (double));
double definite_integral_Simpson(double, double, double (double));

int main(void)
{
    unsigned int partiton = 10;
    printf("The partiton is %u.\n", partiton);
    printf("%lf\n", definite_integral_right     (-2, 1, partiton, fabs));
    printf("%lf\n", definite_integral_trapezium (-2, 1, partiton, fabs));
    printf("%lf\n", definite_integral_Simpson   (-2, 1, fabs));

    return 0;
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