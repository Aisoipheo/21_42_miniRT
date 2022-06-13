/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:16 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:17:50 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "miniRT.h"

static int	rt_mlx_destroy(t_info *info)
{
	if (info->mlx && info->screen.img)
		mlx_destroy_image(info->mlx, info->screen.img);
	if (info->mlx && info->window)
		mlx_destroy_window(info->mlx, info->window);
	return (1);
}

static int	rt_mlx_init(t_info *info)
{
	info->mlx = mlx_init();
	info->window = mlx_new_window(info->mlx, info->w_window,
			info->h_window, RT_TITLE);
	info->screen.img = mlx_new_image(info->mlx, info->w_window, info->h_window);
	info->sky.img = mlx_xpm_file_to_image(info->mlx,
			"resources/sky/sky_map0.xpm", &info->sky.w, &info->sky.h);
	if (info->mlx == NULL || info->window == NULL
		|| info->screen.img == 0 || info->sky.img == 0)
		return (1);
	info->screen.addr = mlx_get_data_addr(info->screen.img, &(info->screen.bpp),
			&(info->screen.size_line), &(info->screen.endian));
	info->sky.addr = mlx_get_data_addr(info->sky.img, &(info->sky.bpp),
			&(info->sky.size_line), &(info->sky.endian));
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->window, EVENT_DESTROY, MASK_NONE, rt_exit_hook, info);
	mlx_hook(info->window, EVENT_KEYPRESS, MASK_NONE, rt_keypress_hook, info);
	return (0);
}
	// mlx_hook(info->window, EVENT_MPRESS, MASK_NONE, rt_mouse_hook, info);

static int	rt_prepare_scene(t_info *info)
{
	info->llo = NULL;
	info->prs_flags = 0;
	info->fov = -1;
	if (rt_parse_map(info))
		return (1);
	rt_select_objs(info);
	if (rt_check_map(info))
		return (1);
	printf("%u objs\n", info->objs.last);
	printf("%u lights\n", info->lights.last);
	rt_calculate_camera(info);
	return (0);
}

int	rt_init(t_info *info)
{
	info->h_window = 9 * 80;
	info->w_window = 16 * 80;
	info->one_w_window = 1.0 / (double)info->w_window;
	info->one_h_window = 1.0 / (double)info->h_window;
	info->one_w_windowm1 = 1.0 / ((double)info->w_window - 1);
	info->one_h_windowm1 = 1.0 / ((double)info->h_window - 1);
	if (rt_mlx_init(info))
		return (rt_error(RT_ERR_INIT, 1));
	if (obj_arr_init(&(info->objs), 0))
		return (rt_error(RT_ERR_INIT, 1));
	if (l_arr_init(&info->lights, 0))
		return (rt_error(RT_ERR_INIT, 1));
	if (rt_prepare_scene(info))
		return (rt_error(RT_ERR_INIT, 0));
	return (0);
}

int	rt_destroy(t_info *info)
{
	free(info->objs.arr);
	if (info->llo)
		free_ll(info->llo);
	rt_mlx_destroy(info);
	return (1);
}
