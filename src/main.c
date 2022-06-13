/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:31 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:30:23 by rdrizzle         ###   ########.fr       */
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

	if (argc != 2)
		return (rt_error("miniRT: bad number of args", 0));
	if (ft_check_arg(argv[1]))
		return (rt_error("miniRT: file extension should be `.rt'", 0));
	info.map = argv[1];
	if (rt_init(&info))
		return (rt_destroy(&info));
	rt_render_image(&info);
	mlx_put_image_to_window(info.mlx, info.window, info.screen.img, 0, 0);
	mlx_loop(info.mlx);
	return (EXIT_FAILURE);
}
