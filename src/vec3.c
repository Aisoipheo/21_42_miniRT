/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:34:25 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 17:48:52 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline t_vec3	vec_zero(void)
{
	t_vec3	self;

	self.e[0] = 0;
	self.e[1] = 0;
	self.e[2] = 0;
	return (self);
}

inline t_vec3	vec_neg(t_vec3 *self)
{
	t_vec3	neg;

	neg.e[0] = -(self->e[0]);
	neg.e[1] = -(self->e[1]);
	neg.e[2] = -(self->e[2]);
	return (neg);
}

inline t_vec3	*vec_add(t_vec3 *self, t_vec3 *other)
{
	self->e[0] += other->e[0];
	self->e[1] += other->e[1];
	self->e[2] += other->e[2];
	return (self);
}

inline t_vec3	*vec_sub(t_vec3 *self, t_vec3 *other)
{
	self->e[0] -= other->e[0];
	self->e[1] -= other->e[1];
	self->e[2] -= other->e[2];
	return (self);
}

inline t_vec3	*vec_mul(t_vec3 *self, double t)
{
	self->e[0] *= t;
	self->e[1] *= t;
	self->e[2] *= t;
	return (self);
}
