/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:04:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:29 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	f_1(t_object *self, t_ray *r, double *d)
{
	t_vec3		pp;
	t_vec3		rv;

	pp = self->p;
	self->p.e[0] = self->p.e[0] - self->u[1] * self->r.e[0];
	self->p.e[1] = self->p.e[1] - self->u[1] * self->r.e[1];
	self->p.e[2] = self->p.e[2] - self->u[1] * self->r.e[2];
	d[0] = rt_hit_plane(self, r);
	rv.e[0] = r->orig.e[0] + r->dir.e[0] * d[0] - self->p.e[0];
	rv.e[1] = r->orig.e[1] + r->dir.e[1] * d[0] - self->p.e[1];
	rv.e[2] = r->orig.e[2] + r->dir.e[2] * d[0] - self->p.e[2];
	d[2] = sqrt(vec_len2(&rv));
	self->p.e[0] = pp.e[0] + self->u[1] * self->r.e[0];
	self->p.e[1] = pp.e[1] + self->u[1] * self->r.e[1];
	self->p.e[2] = pp.e[2] + self->u[1] * self->r.e[2];
	d[1] = rt_hit_plane(self, r);
	rv.e[0] = r->orig.e[0] + r->dir.e[0] * d[1] - self->p.e[0];
	rv.e[1] = r->orig.e[1] + r->dir.e[1] * d[1] - self->p.e[1];
	rv.e[2] = r->orig.e[2] + r->dir.e[2] * d[1] - self->p.e[2];
	d[3] = sqrt(vec_len2(&rv));
	self->p = pp;
}

static double	f_2(t_object *self, double *d)
{
	if (d[1] > 0 || d[0] > 0)
	{
		if (d[0] < d[1])
		{
			if (d[3] <= self->u[0])
				return (d[1]);
			return (-1);
		}
		if (d[2] <= self->u[0])
			return (d[0]);
		return (-1);
	}
	return (-1);
}

double	_rt_hit_cylinder_cap(t_object *self, t_ray *r)
{
	double		d[4];

	f_1(self, r, d);
	if (d[1] > 0 && d[0] > 0)
	{
		if (d[0] < d[1])
		{
			if (d[2] <= self->u[0])
				return (d[0]);
			return (-1);
		}
		if (d[3] <= self->u[0])
			return (d[1]);
		return (-1);
	}
	return (f_2(self, d));
}

// t_point3	_project_on_line(t_point3 *p, t_vec3 *n, t_point3 *o)
// {
// 	t_point3	pp;
// 	t_vec3		ap;
// 	double		d;

// 	ap.e[0] = p->e[0] - o->e[0];
// 	ap.e[1] = p->e[1] - o->e[1];
// 	ap.e[2] = p->e[2] - o->e[2];
// 	d = vec_dot(&ap, &n);
// 	pp.e[0] = o->e[0] + d * n->e[0];
// 	pp.e[0] = o->e[0] + d * n->e[0];
// 	pp.e[0] = o->e[0] + d * n->e[0];
// 	return (pp);
// }

double	_rt_hit_cylinder(t_object *self, t_ray *r)
{
	double		pc[3];
	t_vec3		res;
	t_point3	phit;
	double		d;

	res = r->orig;
	vec_sub(&res, &self->p);
	pc[0] = vec_dot(&r->dir, &self->r);
	pc[2] = vec_dot(&res, &self->r);
	pc[1] = 2.0 * (vec_dot(&r->dir, &res) - pc[0] * pc[2]);
	pc[0] = vec_dot(&r->dir, &r->dir) - pc[0] * pc[0];
	pc[2] = vec_dot(&res, &res) - pc[2] * pc[2] - self->u[0] * self->u[0];
	d = rt_solve(pc);
	if (d == -1)
		return (-1);
	phit.e[0] = r->orig.e[0] + d * r->dir.e[0] - self->p.e[0];
	phit.e[1] = r->orig.e[1] + d * r->dir.e[1] - self->p.e[1];
	phit.e[2] = r->orig.e[2] + d * r->dir.e[2] - self->p.e[2];
	if (fabs(vec_dot(&self->r, &phit)) <= self->u[1])
		return (d);
	return (-1);
}

double	rt_hit_cylinder(t_object *self, t_ray *r)
{
	double	dside;

	dside = _rt_hit_cylinder(self, r);
	if (dside != -1)
		return (dside);
	return (_rt_hit_cylinder_cap(self, r));
}
