/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:16 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/28 14:56:51 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

int	rt_init(t_info *info)
{
	info->w_window = (int)RT_W_SCALE * 80;
	info->h_window = (int)RT_H_SCALE * 80;
	info->u = info->w_window * RT_COLOR_SCALE;
	info->v = info->h_window * RT_COLOR_SCALE;
	if (rt_mlx_init(info))
		return (rt_error(RT_ERR_INIT, 1));
	if (arr_init(&(info->objs), 0))
		return (rt_error(RT_ERR_INIT, 1));
	return (0);
}

int	rt_destroy(t_info *info)
{
	free(info->objs.arr);
	rt_mlx_destroy(info);
	return (1);
}
