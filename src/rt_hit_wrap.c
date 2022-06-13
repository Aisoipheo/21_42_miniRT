/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:54:14 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:34 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	rt_hit_sphere_w(t_object *self, t_ray *r, t_hit *h, double cd)
{
	double	d;

	d = rt_hit_sphere(self, r);
	if (d == -1)
		return (-1);
	if (cd == -1 || (cd != -1 && cd > d))
	{
		h->p = (t_vec3){r->orig.e[0] + r->dir.e[0] * d,
			r->orig.e[1] + r->dir.e[1] * d,
			r->orig.e[2] + r->dir.e[2] * d};
		h->f = 0;
	}
	return (d);
}

double	rt_hit_cylinder_w(t_object *self, t_ray *r, t_hit *h, double cd)
{
	double	d[2];

	d[0] = _rt_hit_cylinder(self, r);
	d[1] = _rt_hit_cylinder_cap(self, r);
	if ((d[0] != -1 && d[1] != -1 && d[0] < d[1]) || (d[0] != -1 && d[1] == -1))
	{
		if (cd == -1 || (cd != -1 && cd > d[0]))
		{
			h->f = 0;
			h->p = (t_vec3){r->orig.e[0] + r->dir.e[0] * d[0],
				r->orig.e[1] + r->dir.e[1] * d[0],
				r->orig.e[2] + r->dir.e[2] * d[0]};
		}
		return (d[0]);
	}
	if (d[1] == -1)
		return (-1);
	if (cd == -1 || (cd != -1 && cd > d[1]))
	{
		h->f = 1;
		h->p = (t_vec3){r->orig.e[0] + r->dir.e[0] * d[1],
			r->orig.e[1] + r->dir.e[1] * d[1],
			r->orig.e[2] + r->dir.e[2] * d[1]};
	}
	return (d[1]);
}

double	rt_hit_plane_w(t_object *self, t_ray *r, t_hit *h, double cd)
{
	double	d;

	d = rt_hit_plane(self, r);
	if (d == -1)
		return (-1);
	if (cd == -1 || (cd != -1 && cd > d))
	{
		h->f = 0;
		h->p = (t_vec3){r->orig.e[0] + r->dir.e[0] * d,
			r->orig.e[1] + r->dir.e[1] * d,
			r->orig.e[2] + r->dir.e[2] * d};
	}
	return (d);
}
