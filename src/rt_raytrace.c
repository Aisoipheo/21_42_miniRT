/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:28:43 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:30:47 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline double	closest_object(t_info *info, t_ray *r, t_hit *h, t_uint hitno)
{
	t_uint	i;
	double	d;
	double	cd;

	cd = -1;
	i = 0;
	while (i != info->objs.last)
	{
		d = (info->objs.arr[i]).hit(&(info->objs.arr[i]), r, h, cd);
		if (cd != -1 && d != -1)
		{
			if (d < cd)
			{
				cd = d;
				info->hits[hitno] = i;
			}
		}
		else if (d != -1)
		{
			cd = d;
			info->hits[hitno] = i;
		}
		++i;
	}
	return (cd);
}

t_color	calculate_color(t_object *obj, t_ray *view_ray, t_ray ln_ray[3],
	t_color *lc)
{
	double	p[3];
	t_color	c[2];
	t_ray	reflection;

	p[0] = ft_dmax(vec_dot(&ln_ray[1].dir, &ln_ray[2].dir), 0.0);
	reflection.orig = ln_ray[0].orig;
	c[0] = vec_neg(&ln_ray[0].dir);
	reflection.dir = vec_reflect(&c[0], ln_ray[1].dir);
	c[0] = vec_neg(&view_ray->dir);
	p[1] = pow(ft_dmax(vec_dot(&c[0], &reflection.dir), 0.0), 32);
	p[2] = 1.0 / vec_len2(&ln_ray[0].dir);
	c[0] = obj->c;
	c[1] = *lc;
	vec_mul(&c[0], p[0] * p[2] * 25);
	vec_mul(&c[1], p[1] * p[2] * 25);
	vec_add(&c[0], &c[1]);
	return (c[0]);
}

static void	f_1(t_info *info, t_ray *r, t_color *c, t_hit *h)
{
	r[0].orig = h->p;
	r[1].orig = h->p;
	r[2].orig = h->p;
	c[0] = info->amb_color;
	vec_mul(&c[0], info->amb_intencity);
}

t_color	iterate_lights(t_info *info, t_hit *h, t_ray *view_ray, t_uint objno)
{
	int		i;
	t_color	c[2];
	t_ray	r[3];
	t_hit	fh;
	double	d;

	f_1(info, r, c, h);
	r[1].dir = (info->objs.arr[objno]).norm(&(info->objs.arr[objno]), h);
	rt_rt_f_3(info, r, view_ray, objno);
	i = info->lights.last;
	while (i--)
	{
		rt_rt_f_2(info, r, h, i);
		d = closest_object(info, &r[2], &fh, RT_MAX_BOUNCE);
		if (d == -1 || info->hits[RT_MAX_BOUNCE] == objno
			|| d > vec_len(&r[0].dir))
		{
			c[1] = calculate_color(&(info->objs.arr[objno]),
					view_ray, r, &info->lights.arr[i].c);
			vec_mul(&c[1], info->lights.arr[i].b);
			vec_add(&c[0], &c[1]);
		}
	}
	return (c[0]);
}

inline void	rt_raytrace(t_info *info, t_ray *r, t_color *c)
{
	t_uint		hits;
	t_hit		h;
	double		d;

	hits = 0;
	d = -1;
	while (hits != RT_MAX_BOUNCE)
	{
		d = closest_object(info, r, &h, hits);
		if (d == -1)
		{
			rt_sky_color(info, r, c);
			return ;
		}
		*c = iterate_lights(info, &h, r, info->hits[hits]);
		vec_norm_rgb(c);
		break ;
		++hits;
	}
}
