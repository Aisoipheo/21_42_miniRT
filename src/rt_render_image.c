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

static inline void	get_color(t_info *info, t_color *c, t_uint x, t_uint y)
{
	t_ray	r;

	r.pos.e[0] = info->cam.pos.e[0];
	r.pos.e[1] = info->cam.pos.e[1];
	r.pos.e[2] = info->cam.pos.e[2];
	r.dir.e[0] = info->cam.dir.e[0];
	r.dir.e[1] = info->cam.dir.e[1];
	r.dir.e[2] = info->cam.dir.e[2];
	c->e[0] = fabs(fmod((255.999 * (r.pos.e[0] + r.dir.e[0])), 256.0));
	c->e[1] = fabs(fmod((255.999 * (r.pos.e[1] + r.dir.e[1])), 256.0));
	c->e[2] = fabs(fmod((255.999 * (r.pos.e[2] + r.dir.e[2])), 256.0));
	(void)x;
	(void)y;
}

void	rt_render_image(t_info *info)
{
	t_uint	i;
	t_uint	j;
	t_color	c;

	// debug
	t_ull	start;
	t_ull	end;

	// should be defined in scene
	info->cam.pos = vec_zero();
	info->cam.dir = vec_zero();
	info->cam.dir.e[2] = -1.0;

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
