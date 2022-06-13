/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:45:17 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:08 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	rt_norm_plane(t_object *self, t_hit *h)
{
	(void)h;
	return (self->r);
}

t_vec3	rt_norm_sphere(t_object *self, t_hit *h)
{
	t_vec3	norm;

	norm = ((t_vec3){
			h->p.e[0] - self->p.e[0],
			h->p.e[1] - self->p.e[1],
			h->p.e[2] - self->p.e[2]
		});
	return (vec_norm(&norm));
}

t_point3	_project_on_line(t_point3 *p, t_vec3 *n, t_point3 *o)
{
	t_point3	pp;
	t_vec3		ap;
	double		d;

	ap.e[0] = p->e[0] - o->e[0];
	ap.e[1] = p->e[1] - o->e[1];
	ap.e[2] = p->e[2] - o->e[2];
	d = vec_dot(&ap, n);
	pp.e[0] = o->e[0] + d * n->e[0];
	pp.e[1] = o->e[1] + d * n->e[1];
	pp.e[2] = o->e[2] + d * n->e[2];
	return (pp);
}

t_vec3	rt_norm_cylinder(t_object *self, t_hit *h)
{
	t_point3	pol;
	t_vec3		norm;

	if (h->f)
	{
		norm = (t_vec3){h->p.e[0] - self->p.e[0],
			h->p.e[1] - self->p.e[1], h->p.e[2] - self->p.e[2]};
		if (vec_dot(&norm, &self->r) < 0)
			return (vec_neg(&self->r));
		return (self->r);
	}
	pol = _project_on_line(&h->p, &self->r, &self->p);
	norm = (t_vec3){h->p.e[0] - pol.e[0], h->p.e[1] - pol.e[1],
		h->p.e[2] - pol.e[2]};
	return (vec_norm(&norm));
}

// t_vec3		_rt_norm_cylinder(t_object *self, t_point3 *p);
// t_vec3		_rt_norm_cylinder_cap(t_object *self, t_point3 *p);
