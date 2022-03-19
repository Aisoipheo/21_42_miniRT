/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:31 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/19 17:36:27 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"

#include <stdio.h>
#include <memory.h>

/* ========= bench / debug ========= */
char	__dline[100];

double	clock_now_usec(void)
{
	struct timeval		t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000000 + t.tv_usec;
}

void	print_time_usec(double usec)
{
	double msec = usec / 1000;
	double sec = msec / 1000;
	double min = sec / 60;

	printf("+%.23s+\n", __dline);
	printf("| min %17.3f |\n", min);
	printf("| sec %17.3f |\n", sec);
	printf("| msec %16.3f |\n", msec);
	printf("| usec %16.3f |\n", usec);
	printf("+%.23s+\n", __dline);
}

void	debug_init(void)
{
	memset(__dline, '-', 100);
}
/* ========= END of bench / debug ========= */

int	main(int argc, char *argv[])
{
	double	start;
	double	end;

	(void)argc;
	(void)argv;
	debug_init();
	start = clock_now_usec();
	printf("Hello!\n");
	end = clock_now_usec();
	return (0);
}
