/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:31 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/29 14:26:03 by rdrizzle         ###   ########.fr       */
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
	mlx_loop(info.mlx);
	return (EXIT_FAILURE);
}
