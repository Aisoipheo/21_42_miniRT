/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:23:21 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/11 14:33:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "miniRT.h"

int	rt_exit_hook(t_info *info)
{
	rt_destroy(info);
	exit(EXIT_SUCCESS);
}

int	rt_keypress_hook(int key, t_info *info)
{
	if (key == KEY_ESC)
		rt_exit_hook(info);
	// if (key == KEY_A)
	// {
	// 	info->cam.orig = vec_neg(&(info->cam.orig));
	// 	info->cam.dir = vec_neg(&(info->cam.dir));
	// 	rt_render_image(info);
	// 	mlx_put_image_to_window(info->mlx, info->window, info->screen.img, 0, 0);
	// }
	return (0);
}

int	rt_mouse_hook(int key, int x, int y, t_info *info)
{
	t_ray	r;
	t_vec3	r2;
	double	w;
	double	x_1;
	double	z_1;

	(void)(key + x + y + info);
	r.orig = info->cam.orig;
	r.dir.e[0] = info->sint0;
	r.dir.e[2] = info->cost0;
	x_1 = r.dir.e[0] * cos(info->theta * (info->w_window - x)) - r.dir.e[2] * sin(info->theta * (info->w_window - x));
	z_1 = r.dir.e[0] * sin(info->theta * (info->w_window - x)) + r.dir.e[2] * cos(info->theta * (info->w_window - x));
	r.dir.e[0] = x_1;
	r.dir.e[2] = z_1;
	r.dir.e[1] = -info->sing0;
	w = info->cosg0;
	x_1 = w * info->cosg - r.dir.e[1] * info->sing;
	z_1 = w * info->sing + r.dir.e[1] * info->cosg;
	z_1 = w * sin(info->gamma * 2.0 * info->one_h_windowm1 * y) + r.dir.e[1] * cos(info->gamma * 2.0 * info->one_h_windowm1 * y);
	x_1 = w * cos(info->gamma * 2.0 * info->one_h_windowm1 * y) - r.dir.e[1] * sin(info->gamma * 2.0 * info->one_h_windowm1 * y);
	w = x_1;
	r.dir.e[1] = z_1;
	r2 = vec_norm(&r.dir);
	printf("     %.4f     %.4f      %.4f\n", r.orig.e[0], r.dir.e[0], r2.e[0]);
	printf("orig %.4f dir %.4f norm %.4f\n", r.orig.e[1], r.dir.e[1], r2.e[1]);
	printf("     %.4f     %.4f      %.4f\n", r.orig.e[2], r.dir.e[2], r2.e[2]);
	printf("\n");
	return (0);
}

int	rt_loop_hook(t_info *info)
{
	(void)info;
	return (0);
}
