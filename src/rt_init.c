/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:16 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/29 18:06:13 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "miniRT.h"

static int	rt_mlx_destroy(t_info *info)
{
	if (info->mlx && info->window)
		mlx_destroy_window(info->mlx, info->window);
	if (info->mlx && info->screen)
		mlx_destroy_image(info->mlx, info->screen);
	return (1);
}

static int	rt_mlx_init(t_info *info)
{
	info->mlx = mlx_init();
	info->window = mlx_new_window(info->mlx, info->w_window,
			info->h_window, RT_TITLE);
	info->screen = mlx_new_image(info->mlx, info->w_window, info->h_window);
	if (info->mlx == NULL || info->window == NULL || info->screen == NULL)
		return (1);
	info->screen_addr = mlx_get_data_addr(info->screen, &(info->bpp),
			&(info->size_line), &(info->endian));
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->window, EVENT_DESTROY, MASK_NONE, rt_exit_hook, info);
	mlx_hook(info->window, EVENT_KEYPRESS, MASK_NONE, rt_keypress_hook, info);
	// mlx_hook(info->window, EVENT_MPRESS, MASK_NONE, mouse_hook, info);
	mlx_loop_hook(info->mlx, rt_loop_hook, info);
	return (0);
}

static int	rt_prepare_scene(t_info *info)
{
	/* --> PARSE HERE! <-- (yes right in this line) */

	// setup camera (should be parsed)
	info->cam.pos = vec_zero();
	info->cam.dir.e[0] = 1;
	info->cam.dir.e[1] = 0;
	info->cam.dir.e[2] = 1;
	info->focal = RT_HALF_W;

	// setup objects (should be parsed)

	// find camera basis && normalize camera dir
	info->b.v[0] = (t_vec3){-info->cam.dir.e[2], 0, info->cam.dir.e[0]};
	if (info->cam.dir.e[0] == 0.0 && info->cam.dir.e[2] == 0.0)
	{
		printf("Bad camera direction! assuming rotation angle = 0\n");
		info->b.v[0] = (t_vec3){info->cam.dir.e[1], 0, 0};
	}
	info->b.v[1] = info->cam.dir;
	vec_cross(&(info->b.v[1]), &(info->b.v[0]));
	if (info->b.v[1].e[1] < 0)
	{
		info->b.v[0] = vec_neg(&(info->b.v[0]));
		info->b.v[1] = vec_neg(&(info->b.v[1]));
	}
	info->b.v[2] = info->cam.dir;
	info->b.v[0] = vec_norm(&(info->b.v[0]));
	info->b.v[1] = vec_norm(&(info->b.v[1]));
	info->b.v[2] = vec_norm(&(info->b.v[2]));
	info->cam.dir = vec_norm(&(info->cam.dir));
	printf("New cam basis:\n");
	printf("   %f    %f    %f\n", info->b.v[0].e[0], info->b.v[1].e[0], info->b.v[2].e[0]);
	printf("v0 %f v1 %f v2 %f\n", info->b.v[0].e[1], info->b.v[1].e[1], info->b.v[2].e[1]);
	printf("   %f    %f    %f\n", info->b.v[0].e[2], info->b.v[1].e[2], info->b.v[2].e[2]);

	return (0);
}

int	rt_init(t_info *info)
{
	info->w_window = (int)RT_W * 80;
	info->h_window = (int)RT_H * 80;
	info->one_w_window = 1.0 / (double)info->w_window;
	info->one_h_window = 1.0 / (double)info->h_window;
	info->u = info->w_window * RT_COLOR_SCALE;
	info->v = info->h_window * RT_COLOR_SCALE;
	if (rt_mlx_init(info))
		return (rt_error(RT_ERR_INIT, 1));
	if (arr_init(&(info->objs), 0))
		return (rt_error(RT_ERR_INIT, 1));
	if (rt_prepare_scene(info))
		return (rt_error(RT_ERR_INIT, 1));
	return (0);
}

int	rt_destroy(t_info *info)
{
	free(info->objs.arr);
	rt_mlx_destroy(info);
	return (1);
}
