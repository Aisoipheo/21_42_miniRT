/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec33.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:15:36 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/23 17:47:34 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	vec_dot(t_vec3 *self, t_vec3 *other)
{
	return (self->e[0] * other->e[0]
		+ self->e[1] * other->e[1]
		+ self->e[2] * other->e[2]
	);
}

//right orthonormal basis
t_vec3	*vec_cross(t_vec3 *self, t_vec3 *other)
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

void	vec_copy(t_vec3 *self, t_vec3 *other)
{
	self->e[0] = other->e[0];
	self->e[1] = other->e[1];
	self->e[2] = other->e[2];
}
