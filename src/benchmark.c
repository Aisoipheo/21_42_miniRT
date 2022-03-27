#include "benchmark.h"

t_ull	clock_now_usec(void)
{
	struct timeval		t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000000ULL + t.tv_usec;
}

void	print_time_usec(t_ull usec)
{
	double msec = (double)usec / 1000;
	double sec = msec / 1000;
	double min = sec / 60;

	printf("+%.23s+\n", __dline);
	printf("| min %17.3f |\n", min);
	printf("| sec %17.3f |\n", sec);
	printf("| msec %16.3f |\n", msec);
	printf("| usec %16.3llu |\n", usec);
	printf("+%.23s+\n", __dline);
}

void	debug_init(void)
{
	memset(__dline, '-', 100);
}
