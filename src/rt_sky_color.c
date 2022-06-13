/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sky_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:40:55 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 17:50:48 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	pixel_get(t_mlx_img *mi, t_color *c, int x, int y)
{
	char	*dst;

	dst = mi->addr + y * mi->size_line + (x * mi->bpp / 8);
	c->e[0] = (((*(unsigned int *)dst) >> 16) & 0xff);
	c->e[1] = (((*(unsigned int *)dst) >> 8) & 0xff);
	c->e[2] = (((*(unsigned int *)dst)) & 0xff);
}

static void	f_1(double *pc, t_ray *r, t_vec3 *r2)
{
	pc[2] = r2->e[2];
	pc[1] = -r->dir.e[1];
	pc[0] = r->dir.e[0];
	pc[4] = pc[6];
	pc[3] = pc[6];
	if (r->dir.e[2] < 0)
	{
		pc[0] = -r->dir.e[0];
		pc[3] = 3 * pc[6];
	}
}

static void	f_2(double *pc, t_ray *r, t_vec3 *r2)
{
	pc[2] = r2->e[0];
	pc[1] = -r->dir.e[1];
	pc[0] = -r->dir.e[2];
	pc[4] = pc[6];
	pc[3] = 2 * pc[6];
	if (r->dir.e[0] < 0)
	{
		pc[0] = r->dir.e[2];
		pc[3] = 0;
	}
}

static void	f_3(double *pc, t_ray *r, t_vec3 *r2)
{
	pc[2] = r2->e[1];
	pc[0] = r->dir.e[0];
	pc[1] = r->dir.e[2];
	pc[3] = pc[6];
	pc[4] = 0;
	if (r->dir.e[1] < 0)
	{
		pc[1] = -r->dir.e[2];
		pc[4] = 2 * pc[6];
	}
}

inline void	rt_sky_color(t_info *info, t_ray *r, t_color *c)
{
	t_vec3	r2;
	double	pc[7];

	pc[6] = 1024.0;
	pc[5] = 511.999;
	r2.e[0] = fabs(r->dir.e[0]);
	r2.e[1] = fabs(r->dir.e[1]);
	r2.e[2] = fabs(r->dir.e[2]);
	if (r2.e[2] >= r2.e[0] && r2.e[2] >= r2.e[1])
		f_1(pc, r, &r2);
	if (r2.e[0] >= r2.e[1] && r2.e[0] >= r2.e[2])
		f_2(pc, r, &r2);
	if (r2.e[1] >= r2.e[0] && r2.e[1] >= r2.e[2])
		f_3(pc, r, &r2);
	pc[1] = (pc[1] * (1.0 / pc[2]) + 1.0) * pc[5];
	pc[0] = (pc[0] * (1.0 / pc[2]) + 1.0) * pc[5];
	pixel_get(&(info->sky), c, pc[3] + pc[0], pc[4] + pc[1]);
}
