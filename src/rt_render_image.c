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

static inline void	pixel_put(t_mlx_img *mi, t_color *c, int x, int y)
{
	char	*dst;

	dst = mi->addr + y * mi->size_line + (x * mi->bpp / 8);
	*(unsigned int *)dst = (((int)c->e[0]) << 16)
		| (((int)c->e[1]) << 8)
		| (((int)c->e[2]));
}

static inline void	pixel_get(t_mlx_img *mi, t_color *c, int x, int y)
{
	char	*dst;

	dst = mi->addr + y * mi->size_line + (x * mi->bpp / 8);
	c->e[0] = (((*(unsigned int *)dst) >> 16) & 0xff);
	c->e[1] = (((*(unsigned int *)dst) >> 8) & 0xff);
	c->e[2] = (((*(unsigned int *)dst)) & 0xff);
}

// +x r
// +y u
// +z f
inline void	rt_sky_color(t_info *info, t_ray *r, t_color *c)
{
	t_vec3	r2;
	double	pc[5];
	double	s = 256;
	double	ss = 127.999;

	r2.e[0] = fabs(r->dir.e[0]);
	r2.e[1] = fabs(r->dir.e[1]);
	r2.e[2] = fabs(r->dir.e[2]);
	if (r2.e[2] >= r2.e[0] && r2.e[2] >= r2.e[1]) // z-axis f b
	{
		pc[2] = r2.e[2];
		pc[1] = -r->dir.e[1];
		pc[0] = r->dir.e[0];
		pc[4] = s;
		pc[3] = s;
		if (r->dir.e[2] < 0)
		{
			pc[0] = -r->dir.e[0];
			pc[3] = 3 * s;
		}
	}
	if (r2.e[0] >= r2.e[1] && r2.e[0] >= r2.e[2]) // x-axis r l
	{
		pc[2] = r2.e[0];
		pc[1] = -r->dir.e[1];
		pc[0] = -r->dir.e[2];
		pc[4] = s;
		pc[3] = 2 * s;
		if (r->dir.e[0] < 0)
		{
			pc[0] = r->dir.e[2];
			pc[3] = 0;
		}
	}
	if (r2.e[1] >= r2.e[0] && r2.e[1] >= r2.e[2]) // y-axis u d
	{
		pc[2] = r2.e[1];
		pc[0] = r->dir.e[0];
		pc[1] = r->dir.e[2];
		pc[3] = s;
		pc[4] = 0;
		if (r->dir.e[1] < 0)
		{
			pc[1] = -r->dir.e[2];
			pc[4] = 2 * s;
		}
	}
	pc[1] = (pc[1] * (1.0 / pc[2]) + 1.0) * ss;
	pc[0] = (pc[0] * (1.0 / pc[2]) + 1.0) * ss;
	pixel_get(&(info->sky), c, pc[3] + pc[0], pc[4] + pc[1]);
}

// static inline void	ray_color(t_info *info, t_ray *r, t_color *c)
// {
// 	t_ray	r;
// 	// t_vec3	support;
// 	double	x_0;
// 	double	y_0;

// 	// support.e[0] = info->cam.orig.e[0] + info->b.v[0].e[0] * x_0 + info->b.v[1].e[0] * x_0;
// 	// support.e[1] = info->cam.orig.e[1] - info->b.v[1].e[1] * y_0;
// 	// support.e[2] = info->cam.orig.e[2] + info->b.v[0].e[2] * x_0 + info->b.v[1].e[2] * x_0;
// 	r.orig = info->cam.orig;
// 	// r.dir.e[0] = support.e[0] - (info->cam.orig.e[0] - info->b.v[2].e[0] * info->focal);
// 	// r.dir.e[1] = support.e[1] - (info->cam.orig.e[1] - info->b.v[2].e[1] * info->focal);
// 	// r.dir.e[2] = support.e[2] - (info->cam.orig.e[2] - info->b.v[2].e[2] * info->focal);
// 	r.dir = vec_norm(&(r.dir));
// 	rt_raytrace(info, &r, c);
// }

void	rt_render_image(t_info *info)
{
	t_uint	i;
	t_uint	j;
	t_color	c;
	t_ray	r;
	t_ray	norm;
	double	w;
	double	x_1;
	double	z_1;

	// debug
	t_ull	start;
	t_ull	end;

	i = info->h_window;
	r.orig = info->cam.orig;
	norm.orig = r.orig;
	r.dir.e[1] = -info->sing0;
	w = info->cosg0;
	printf("Rendering...\n");
	start = clock_now_usec();
	while (i--)
	{
		j = info->w_window;
		r.dir.e[0] = info->sint0;
		r.dir.e[2] = info->cost0;
		while (j--)
		{
			norm.dir.e[0] = r.dir.e[0] * info->b.v[0].e[0] + r.dir.e[1] * info->b.v[1].e[0] + r.dir.e[2] * info->b.v[2].e[0];
			norm.dir.e[1] = r.dir.e[0] * info->b.v[0].e[1] + r.dir.e[1] * info->b.v[1].e[1] + r.dir.e[2] * info->b.v[2].e[1];
			norm.dir.e[2] = r.dir.e[0] * info->b.v[0].e[2] + r.dir.e[1] * info->b.v[1].e[2] + r.dir.e[2] * info->b.v[2].e[2];
			norm.dir = vec_norm(&norm.dir);
			rt_raytrace(info, &norm, &c);
			pixel_put(&(info->screen), &c, j, i);
			x_1 = r.dir.e[0] * info->cost - r.dir.e[2] * info->sint;
			z_1 = r.dir.e[0] * info->sint + r.dir.e[2] * info->cost;
			r.dir.e[0] = x_1;
			r.dir.e[2] = z_1;
		}
		x_1 = w * info->cosg - r.dir.e[1] * info->sing;
		z_1 = w * info->sing + r.dir.e[1] * info->cosg;
		w = x_1;
		r.dir.e[1] = z_1;
		printf("\r%f", (1.0 - (double)i / info->h_window) * 100.0);
		fflush(stdout);
	}
	end = clock_now_usec();
	printf("\nReady!\n");
	print_time_usec(end - start);
}
