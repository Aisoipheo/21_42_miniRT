/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:13:23 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/28 16:21:06 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "miniRT.h"
#include "benchmark.h"

static inline void	pixel_put(t_info *info, t_color *color, int x, int y)
{
	char	*dst;

	dst = info->screen_addr + y * info->size_line + (x * info->bpp / 8);
	*(unsigned int *)dst = (((int)color->e[0]) << 16)
		| (((int)color->e[1]) << 8)
		| (((int)color->e[2]));
}

static inline void	get_color(t_info *info, t_color *c, double x, double y)
{
	t_ray	r;
	double	x_0;
	double	y_0;

	x_0 = (RT_W * x * info->one_w_window - RT_HALF_W);
	y_0 = (RT_H * y * info->one_h_window - RT_HALF_H);
	r.pos.e[0] = info->cam.pos.e[0] + info->b.v[0].e[0] * x_0 + info->b.v[1].e[0] * y_0;
	r.pos.e[1] = info->cam.pos.e[1] + info->b.v[1].e[1] * y_0;
	r.pos.e[2] = info->cam.pos.e[2] + info->b.v[0].e[2] * x_0 + info->b.v[1].e[2] * y_0;
	r.dir.e[0] = r.pos.e[0] - (info->cam.pos.e[0] - info->b.v[2].e[0] * info->focal);
	r.dir.e[1] = r.pos.e[1] - (info->cam.pos.e[1] - info->b.v[2].e[1] * info->focal);
	r.dir.e[2] = r.pos.e[2] - (info->cam.pos.e[2] - info->b.v[2].e[2] * info->focal);
	r.dir = vec_norm(&(r.dir));
	c->e[0] = (255.999 * r.dir.e[0] + 256.0) / 2;
	c->e[1] = (255.999 * r.dir.e[1] + 256.0) / 2;
	c->e[2] = (255.999 * r.dir.e[2] + 256.0) / 2;
}

void	rt_render_image(t_info *info)
{
	t_uint	i;
	t_uint	j;
	t_color	c;

	// debug
	t_ull	start;
	t_ull	end;

	i = info->h_window;
	printf("Rendering...\n");
	start = clock_now_usec();
	while (i--)
	{
		j = info->w_window;
		while (j--)
		{
			get_color(info, &c, j, i);
			pixel_put(info, &c, j, i);
		}
		printf("\r%f", (1.0 - (double)i / info->h_window) * 100.0);
		fflush(stdout);
	}
	end = clock_now_usec();
	printf("\nReady!\n");
	print_time_usec(end - start);
}
