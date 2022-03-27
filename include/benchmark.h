/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:53:58 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 16:40:50 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include <sys/time.h>
# include <sys/resource.h>
# include <memory.h>
# include <stdio.h>

typedef unsigned long long int	t_ull;

char	__dline[100];

void	debug_init(void);
t_ull	clock_now_usec(void);
void	print_time_usec(t_ull usec);

#endif
