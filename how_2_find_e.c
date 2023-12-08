#include "limit.c"

#define OBSERVE_TIME 1

#define H_APPROACH_0 0.000001
#define CLOCK_DIFF   (end - begin)
#define TIME_DIFF    ((double)(end - begin) / CLOCKS_PER_SEC)

static clock_t begin, end;

void by_Riemann_sum(void);
void by_compound_interest(void);
void by_Taylor_expansion(void);

double f(double x)
{
    return (1/x);
}

int main(void)
{
    by_Riemann_sum();
    //by_compound_interest();
    //by_Taylor_expansion();
}

void by_Riemann_sum(void)
{
    register double x;
    register uint64_t foo = 0;

	if(fabs(definite_integral_right(1.0, E, 100000, f) - 1.0) < H_APPROACH_0)
    {
    	printf("aasdf");
    	return ;
	}
	printf("%lf %lf\n", fabs(definite_integral_right(1.0, E, 364599, f) - 1.0), H_APPROACH_0);
    return;

    int i = 1;
    for(; fabs(definite_integral_right(1.0, E, i, f) - 1.0) > H_APPROACH_0; ++i)
    {
    	printf("%d %lf\n", i, fabs(definite_integral_right(1.0, E, i, f) - 1.0));
	}
    return;
    
    //By definite_integral_right.
    x = 1.0;
    begin = clock();
    while(1)
    {
        if(fabs(definite_integral_right(1.0, E, 100000, f) - 1.0) < H_APPROACH_0)
        {
            break;
        }

        x += H_APPROACH_0;
    }
    end = clock();

#ifdef OBSERVE_TIME
    printf("by_Riemann_sum::definite_integral_right: |%lf|\n", TIME_DIFF);
#else
    printf("by_Riemann_sum::definite_integral_right: |%llu|\n", (uintmax_t)CLOCK_DIFF);
#endif

    //By definite_integral_midpoint.
    x = 1.0;
    begin = clock();
    while(1)
    {
        if(fabs(definite_integral_midpoint(1.0, x, 10000, f) - 1.0) < H_APPROACH_0)
        {
            break;
        }

        x += H_APPROACH_0;
    }
    end = clock();

#ifdef OBSERVE_TIME
    printf("by_Riemann_sum::definite_integral_midpoint: |%lf|\n", TIME_DIFF);
#else
    printf("by_Riemann_sum::definite_integral_midpoint: |%llu|\n", (uintmax_t)CLOCK_DIFF);
#endif

    //By definite_integral_trapezium.
    x = 1.0;
    begin = clock();
    while(1)
    {
        if(fabs(definite_integral_trapezium(1.0, x, 10000, f) - 1.0) < H_APPROACH_0)
        {
            break;
        }

        x += H_APPROACH_0;
    }
    end = clock();

#ifdef OBSERVE_TIME
    printf("by_Riemann_sum::definite_integral_trapezium: |%lf|\n", TIME_DIFF);
#else
    printf("by_Riemann_sum::definite_integral_trapezium: |%llu|\n", (uintmax_t)CLOCK_DIFF);
#endif

    //By definite_integral_Simpson_1_3.
    x = 1.0;
    begin = clock();
    while(1)
    {
        if(fabs(definite_integral_Simpson_1_3(1.0, x, 10000, f) - 1.0) < H_APPROACH_0)
        {
            break;
        }

        x += H_APPROACH_0;
    }
    end = clock();

#ifdef OBSERVE_TIME
    printf("by_Riemann_sum::definite_integral_Simpson_1_3: |%lf|\n", TIME_DIFF);
#else
    printf("by_Riemann_sum::definite_integral_Simpson_1_3: |%llu|\n", (uintmax_t)CLOCK_DIFF);
#endif

    //By definite_integral_Simpson_3_8.
    x = 1.0;
    begin = clock();
    while(1)
    {
        if(fabs(definite_integral_Simpson_3_8(1.0, x, 10000, f) - 1.0) < H_APPROACH_0)
        {
            break;
        }

        x += H_APPROACH_0;
    }
    end = clock();

#ifdef OBSERVE_TIME
    printf("by_Riemann_sum::definite_integral_Simpson_3_8: |%lf|\n", TIME_DIFF);
#else
    printf("by_Riemann_sum::definite_integral_Simpson_3_8: |%llu|\n", (uintmax_t)CLOCK_DIFF);
#endif
}

void by_compound_interest(void)
{
    begin = clock();

    

    end = clock();
    printf("by_Riemann_sum: |%lf|", end - begin);
}

void by_Taylor_expansion(void)
{
    begin = clock();

    

    end = clock();
    printf("by_Riemann_sum: |%lf|", end - begin);
}
