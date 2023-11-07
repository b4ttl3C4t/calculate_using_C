#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

void   limit_to_zero            (double (*)(double));
double iter_bisect_method       (double);
double Newton_method            (double, double (double));
int8_t Newton_stopping_criteria (double, double, double, double);
double Taylor_series            (uint8_t, double, double, double (double));
double Lagrange_polynomial      (uint8_t, ...);

void   first_differentiation            (double (double));
double first_right_derivative           (double, double, double (double));
double first_symmetric_derivative       (double, double, double (double));
double first_five_point_derivative      (double, double, double (double));

void   second_differentiation           (double (double));
double second_right_derivative          (double, double, double (double));
double second_symmetric_derivative      (double, double, double (double));
double second_five_point_derivative     (double, double, double (double));

void   iterative_differentiation        (double (double));
void   recursive_differentiation        (double (double));
double recursive_right_derivative       (uint8_t, double, double, double (double));
double recursive_symmetric_derivative   (uint8_t, double, double, double (double));
double recursive_five_point_derivative  (uint8_t, double, double, double (double));

void   numerical_integration        (double (double));
double definite_integral_right      (double, double, double, double (double));
double definite_integral_trapezium  (double, double, double, double (double));
double definite_integral_Simpson    (double, double, double (double));