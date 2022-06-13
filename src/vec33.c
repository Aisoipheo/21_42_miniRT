/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec33.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:15:36 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/10 16:57:21 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline double	vec_dot(t_vec3 *self, t_vec3 *other)
{
	return (self->e[0] * other->e[0]
		+ self->e[1] * other->e[1]
		+ self->e[2] * other->e[2]
	);
}

//right orthonormal basis
inline t_vec3	*vec_cross(t_vec3 *self, t_vec3 *other)
{
	t_vec3	vec;

	vec.e[0] = self->e[1] * other->e[2] - self->e[2] * other->e[1];
	vec.e[1] = self->e[2] * other->e[0] - self->e[0] * other->e[2];
	vec.e[2] = self->e[0] * other->e[1] - self->e[1] * other->e[0];
	self->e[0] = vec.e[0];
	self->e[1] = vec.e[1];
	self->e[2] = vec.e[2];
	return (self);
}

t_vec3	vec_reflect(t_vec3 *self, t_vec3 normal)
{
	t_vec3	reflection;

	reflection = *self;
	vec_sub(&reflection, vec_mul(&normal, vec_dot(self, &normal) * 2.0));
	return (vec_norm(&reflection));
}

void	vec_norm_rgb(t_vec3	*self)
{
	self->e[0] = ft_dmax(self->e[0], 0.0);
	self->e[1] = ft_dmax(self->e[1], 0.0);
	self->e[2] = ft_dmax(self->e[2], 0.0);
	self->e[0] = ft_dmin(self->e[0], 255.99);
	self->e[1] = ft_dmin(self->e[1], 255.99);
	self->e[2] = ft_dmin(self->e[2], 255.99);
}

// inline void	vec_copy(t_vec3 *self, t_vec3 *other)
// {
// 	self->e[0] = other->e[0];
// 	self->e[1] = other->e[1];
// 	self->e[2] = other->e[2];
// }
