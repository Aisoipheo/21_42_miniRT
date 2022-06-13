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

static void	f_1(t_info *info, t_uint *pi, t_ray *rr, double *px)
{
	pi[0] = info->h_window;
	rr[0].orig = info->cam.orig;
	rr[1].orig = rr[0].orig;
	rr[0].dir.e[1] = -info->sing0;
	px[0] = info->cosg0;
}

static void	f_2(t_info *info, t_ray *rr, double *px)
{
	px[1] = rr[0].dir.e[0] * info->cost - rr[0].dir.e[2] * info->sint;
	px[2] = rr[0].dir.e[0] * info->sint + rr[0].dir.e[2] * info->cost;
	rr[0].dir.e[0] = px[1];
	rr[0].dir.e[2] = px[2];
}

static void	f_3(t_info *info, t_ray *rr)
{
	rr[1].dir.e[0] = rr[0].dir.e[0] * info->b.v[0].e[0] + rr[0].dir.e[1]
		* info->b.v[1].e[0] + rr[0].dir.e[2] * info->b.v[2].e[0];
	rr[1].dir.e[1] = rr[0].dir.e[0] * info->b.v[0].e[1] + rr[0].dir.e[1]
		* info->b.v[1].e[1] + rr[0].dir.e[2] * info->b.v[2].e[1];
	rr[1].dir.e[2] = rr[0].dir.e[0] * info->b.v[0].e[2] + rr[0].dir.e[1]
		* info->b.v[1].e[2] + rr[0].dir.e[2] * info->b.v[2].e[2];
	rr[1].dir = vec_norm(&rr[1].dir);
}

void	rt_render_image(t_info *info)
{
	t_uint	pi[2];
	t_color	c;
	t_ray	rr[2];
	double	px[3];

	f_1(info, pi, rr, px);
	while (pi[0]--)
	{
		pi[1] = info->w_window;
		rr[0].dir.e[0] = info->sint0;
		rr[0].dir.e[2] = info->cost0;
		while (pi[1]--)
		{
			f_3(info, rr);
			rt_raytrace(info, &rr[1], &c);
			pixel_put(&(info->screen), &c, pi[1], pi[0]);
			f_2(info, rr, px);
		}
		px[1] = px[0] * info->cosg - rr[0].dir.e[1] * info->sing;
		px[2] = px[0] * info->sing + rr[0].dir.e[1] * info->cosg;
		px[0] = px[1];
		rr[0].dir.e[1] = px[2];
	}
}
