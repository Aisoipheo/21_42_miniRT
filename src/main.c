/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:31 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/28 17:14:04 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	rt_render_image(&info);
	mlx_put_image_to_window(info.mlx, info.window, info.screen, 0, 0);
	t_vec3 a;
	a.e[0] = 3;
	a.e[1] = 6;
	a.e[2] = 5;
	a = vec_norm(&a);
	printf("%f %f %f\n", a.e[0], a.e[1], a.e[2]);
	mlx_loop(info.mlx);
	return (EXIT_FAILURE);
}
