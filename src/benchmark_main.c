#include "fastmath.h"
#include "benchmark.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

typedef unsigned long long int t_ull;

// void	fast_demo(void)
// {
// 	double a = 123.123456789;
// 	double b = -a * 2;

// }

double	lvl0_fast(double f0)
{
	return fast_sqrt(f0);
}

double	lvl0_double(double d0)
{
	return sqrt(d0);
}

void	bench0_fast(double *arr, t_ull size)
{
	for (t_ull i = 0; i < size; ++i)
		arr[i] = lvl0_fast(i);
}

void	bench0_double(double *arr, t_ull size)
{
	for (t_ull i = 0; i < size; ++i)
		arr[i] = lvl0_double(i);
}

void	work(double *arr1, double *arr2, t_ull size)
{
	FILE *f = fopen("work.txt", "w");

	for (t_ull i = 0; i < size; ++i)
		fprintf(f, "%f - %f = %f\n", arr1[i], arr2[i], arr1[i] - arr2[i]);
	fclose(f);
}

void	bench_lvl0(void)
{
	double	fstart, fend, ftime;
	double	dstart, dend, dtime;
	t_ull	size = 1000000; // 1 mil

	double	*farr = (double *)malloc(sizeof(double) * size);
	double	*darr = (double *)malloc(sizeof(double) * size);

	fstart = clock_now_usec();
	bench0_fast(farr, size);
	fend = clock_now_usec();
	ftime = fend - fstart;

	dstart = clock_now_usec();
	bench0_double(darr, size);
	dend = clock_now_usec();
	dtime = dend - dstart;

	work(darr, farr, size);

	printf("Fast:\n");
	print_time_usec(ftime);
	printf("\nDouble:\n");
	print_time_usec(dtime);
	printf("\nLvl0 ratio: %f\n", dtime / ftime);
	free(farr);
	free(darr);
}

int main(void)
{
	debug_init();
	bench_lvl0();
	return (0);
}
