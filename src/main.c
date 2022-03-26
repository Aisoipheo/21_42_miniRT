/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:31 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 15:34:09 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "vec3.h"
#include "benchmark.h"

int	main(int argc, char *argv[])
{
	t_info	info;
	(void)argc;
	(void)argv;
	debug_init();
	if (rt_init(&info))
		return (rt_destroy(&info));
	return (0);
}
