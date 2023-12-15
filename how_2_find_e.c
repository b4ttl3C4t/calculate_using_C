#include <stdint.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define H_APPROACH_0 0.000001
#define UPPER_LIMIT  1E18

#define CLOCK_DIFF (end - begin)
#define TIME_DIFF ((double)(end - begin) / CLOCKS_PER_SEC)
#define E 2.718281

static clock_t begin, end;

void exhaustive_by_Riemann_sum(void);
void binary_by_Riemann_sum(void);
void by_compound_interest(void);
void by_Taylor_expansion(void);

inline static double 	fast_power(double, uint64_t);
inline static uint64_t	factorial(uint32_t);

inline static double definite_integral_right(double, double, uint64_t, double(double));
inline static double definite_integral_midpoint(double, double, uint64_t, double(double));
inline static double definite_integral_trapezium(double, double, uint64_t, double(double));
inline static double definite_integral_proportion(double, double, uint64_t, double(double));
inline static double first_symmetric_derivative(double, double, double(double));

double f(double x)
{
	return (1 / x);
}

int main(void)
{
	binary_by_Riemann_sum();
	by_compound_interest();
	by_Taylor_expansion();
	//exhaustive_by_Riemann_sum();
}

void exhaustive_by_Riemann_sum(void)
{
	register double x;

	// By definite_integral_trapezium.
	begin = clock();
	x = 1.0;
	while (1)
	{
		if (fabs(definite_integral_trapezium(1.0, x, 100, f) - 1.0) < H_APPROACH_0)
		{
			break;
		}

		x += H_APPROACH_0;
	}
	end = clock();
	printf("exhaustive_by_Riemann_sum::trapezium:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   x,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);

	// By definite_integral_midpoint.
	begin = clock();
	x = 1.0;
	while (1)
	{
		if (fabs(definite_integral_midpoint(1.0, x, 100, f) - 1.0) < H_APPROACH_0)
		{
			break;
		}

		x += H_APPROACH_0;
	}
	end = clock();
	printf("exhaustive_by_Riemann_sum::midpoint:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   x,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);

	// By definite_integral_right.
	begin = clock();
	x = 1.0;
	while (1)
	{
		if (fabs(definite_integral_right(1.0, x, 100, f) - 1.0) < H_APPROACH_0)
		{
			break;
		}

		x += H_APPROACH_0;
	}
	end = clock();
	printf("exhaustive_by_Riemann_sum::right:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   x,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
}

// Also by mean value theorem.
void binary_by_Riemann_sum(void)
{
	register double temp, mid, lower, upper;
/*
	// By table-search method.
	begin = clock();
	lower = 1.0;
	upper = UPPER_LIMIT;
	while (1)
	{
		mid = (lower + upper) / 2;
		temp = definite_integral_proportion(1.0, mid, 1000000000, f);
		if (fabs(temp - 1.0) < 0.0000000001)
		{
			break;
		}

		if (temp < 1.0)
		{
			lower = mid;
		}
		else
		{
			upper = mid;
		}
	}
	end = clock();
	printf("binary_by_Riemann_sum::table:\t\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   mid,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
*/
	// By trapezium.
	begin = clock();
	lower = 1.0;
	upper = DBL_MAX;
	while (1)
	{
		mid = (lower + upper) / 2;
		temp = definite_integral_trapezium(1.0, mid, 870, f);
		/* The loop is going to be terminated
		 * when the difference between the area of the define integral and constant 1 is less than a small number.
		 */
		if (fabs(temp - 1.0) < H_APPROACH_0)
		{
			break;
		}
		if (temp < 1.0)
			lower = mid;
		else
			upper = mid;
	}
	end = clock();
	printf("binary_by_Riemann_sum::trapezium:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   mid,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
/* 
	// By midpoint.
	begin = clock();
	lower = 1.0;
	upper = DBL_MAX;
	while (1)
	{
		mid = (lower + upper) / 2;
		temp = definite_integral_midpoint(1.0, mid, 2200, f);
		if (fabs(temp - 1.0) < H_APPROACH_0)
		{
			break;
		}

		if (temp < 1.0)
			lower = mid;
		else
			upper = mid;
	}
	end = clock();
	printf("binary_by_Riemann_sum::midpoint:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   mid,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);

	// By right.
	begin = clock();
	lower = 1.0;
	upper = DBL_MAX;
	while (1)
	{
		mid = (lower + upper) / 2;
		temp = definite_integral_right(1.0, mid, 100000, f);
		if (fabs(temp - 1.0) < H_APPROACH_0)
		{
			break;
		}

		if (temp < 1.0)
			lower = mid;
		else
			upper = mid;
	}
	end = clock();
	printf("binary_by_Riemann_sum::right:\t\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   mid,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
*/ 
}

void by_compound_interest(void)
{
	register double prev, product;
	register uint64_t i, n;
/*
	// By log10() and exp10() (table-search method).
	begin = clock();
	product = exp(log(1 + 1.0 / 2000000) * 2000000);
	end = clock();
	printf("by_compound_interest::table:\t\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   product,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
*/
	// By bit-by-bit method.
	begin = clock();
	n = UINT_MAX;
	prev = 0.0;
	for(i = 1; i <= n; ++i)
	{
		product = fast_power(1.0 + 1.0 / i, i);
		/* The loop is going to be terminated
		 * when the latter term and the former one is identical.
		 * (The convergence speed is too slow to use *product - prev < (SMALL_NUMBER)*)
		 */
		if(product == prev)
		{
			break;
		}
		prev = product;
	}
	end = clock();
	printf("by_compound_interest::bit-by-bit:\t result:|%.7lf| sec:|%lf| clock:|%llu|\n",
		   product,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
/* 
	// By iterative method.
	begin = clock();
	n = UINT_MAX;
	product = 1.0;
	term = 1 + 1.0 / n;
	for (i = 0; i < n; ++i)
	{
		product *= term;
	}
	end = clock();
	printf("by_compound_interest::iterative:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n",
		   product,
		   TIME_DIFF,
		   (uintmax_t)CLOCK_DIFF);
*/ 
}

void by_Taylor_expansion(void)
{
	register double term, sum, temp;
	register uint64_t i;
/*
	// By multiplication.
	begin = clock();
	term = 1.0 / factorial(10);
	sum = 1.0;
    for(i = 10; i >= 1; --i)
    {
    	sum += term;
		term *= i;
	}
	end = clock();
    printf("by_Taylor_expansion::multiplication:\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n", 
			sum,
			TIME_DIFF, 
			(uintmax_t)CLOCK_DIFF);
*/
	//by division
	begin = clock();
	term = sum = 1.0;
    for(i = 1; i < UINT_MAX; ++i)
    {
    	term /= i;
    	temp = sum;
    	sum += term;
    	/* Each more term could make the *sum* more accurate.
    	 * Therefore, check the difference of both could determine the time to break out of the loop.
    	 */
    	if(sum - temp < H_APPROACH_0)
		{
			break;
		}
	}
	end = clock();
    printf("by_Taylor_expansion::division:\t\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n", 
			sum,
			TIME_DIFF, 
			(uintmax_t)CLOCK_DIFF);
/* 
	//by factorial
	begin = clock();
	sum = 0;
    for(i = 0; i < UINT_MAX; ++i)
    {
    	term = sum;
		sum += 1.0 / factorial(i);
		if(sum - term < H_APPROACH_0)
		{
			break;
		}
	}
	end = clock();
    printf("by_Taylor_expansion::factorial:\t\t result:|%.7lf| sec:|%lf| clock:|%llu|.\n", 
			sum,
			TIME_DIFF, 
			(uintmax_t)CLOCK_DIFF);
*/ 
}

// Calculating definite integral by right side height.
static double definite_integral_right(double lower, double upper, uint64_t n, double f(double))
{
	double summation = 0.0;
	double height = 0.0;
	double dx = (upper - lower) / n;
	uint32_t i;

	for (i = 1; i <= n; ++i)
	{
		/*Obtaining the approximate summation of f (integral from lower to upper)
		 *by calculating the height multiple the dx step by step.
		 */
		height = f(lower + i * dx);
		summation += height;
	}

	// You can move out the multiplication of dx by distributive property.
	summation *= dx;

	return summation;
}

// Calculating definite integral by midpoint height.
static double definite_integral_midpoint(double lower, double upper, uint64_t n, double f(double))
{
	double summation = 0.0;
	double height = 0.0;
	double dx = (upper - lower) / n;
	uint32_t i;

	for (i = 0; i <= n - 1; ++i)
	{
		height = f(lower + ((2 * i + 1) * dx) / 2.0);
		summation += height;
	}

	// You can move out the multiplication of dx by distributive property.
	summation *= dx;

	return summation;
}

// Calculating definite integral by trapezium.
static double definite_integral_trapezium(double lower, double upper, uint64_t n, double f(double))
{
	double summation = 0.0;
	double height = 0.0;
	double dx = (upper - lower) / n;
	uint32_t i;

	summation += (f(lower) + f(upper)) / 2;

	for (i = 1; i < n; ++i)
	{
		height = f(lower + i * dx);
		summation += height;
	}

	// You can move out the multiplication of dx by distributive property.
	summation *= dx;

	return summation;
}

static double first_symmetric_derivative(double x, double h, double f(double))
{
	return (f(x + h) - f(x - h)) / (2 * h);
}

// The exp and log can be replaced by exp10 and log10 (but it still not meet the conditions (not using Euler number)).
static double definite_integral_proportion(double lower, double upper, uint64_t n, double f(double))
{
	return first_symmetric_derivative((exp(log(upper / lower) * (1.0 / n)) - 1.0), H_APPROACH_0, f) /
		   first_symmetric_derivative(1.0 / n, H_APPROACH_0, f);
}

static inline uint64_t factorial(uint32_t n)
{
	uint64_t result, i;

	if (n == 0 || n == 1)
	{
		return 1;
	}

	result = 1;
	for (i = 2; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

static double fast_power(double x, uint64_t n)
{
	double result = 1;

	while (n)
	{
		if (n & 1)
		{
			result *= x;
		}
		x *= x;
		n >>= 1;
	}
	return result;
}
