/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:04:00 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/16 17:19:34 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// -1 or dist to hit point from ray origin
inline double	rt_solve(double *pc)
{
	double	res[4];

	res[3] = pc[1] * pc[1] - 4 * pc[0] * pc[2];
	res[2] = 1.0 / (2 * pc[0]);
	if (res[3] < 0.)
		return (-1);
	res[3] = sqrt(res[3]);
	res[0] = (-pc[1] - res[3]) * res[2];
	res[1] = (-pc[1] + res[3]) * res[2];
	if (res[0] > RT_EPS && res[1] > RT_EPS)
	{
		if (res[0] > res[1])
			return (res[1]);
		return (res[0]);
	}
	if (res[0] > RT_EPS || res[1] > RT_EPS)
	{
		if (res[0] < res[1])
			return (res[1]);
		return (res[0]);
	}
	return (-1);
}

double	rt_hit_sphere(t_object *self, t_ray *r)
{
	double	pc[3];
	t_vec3	res;

	res = r->orig;
	vec_sub(&res, &self->p);
	pc[0] = 1.;
	pc[1] = 2.0 * vec_dot(&res, &r->dir);
	pc[2] = vec_dot(&res, &res) - self->u[0] * self->u[0];
	return rt_solve(pc);
}


double	rt_hit_plane(t_object *self, t_ray *r)
{
	t_vec3	res;
	double	a;
	double	b;

	a = vec_dot(&self->r, &r->dir);
	if (fabs(a) < RT_EPS)
		return (-1);
	res = r->orig;
	b = -(vec_dot(vec_sub(&res, &self->p), &self->r)) * (1.0 / a);
	if (b < 0)
		return (-1);
	return (b);
}
