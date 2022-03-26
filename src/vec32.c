/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:50:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/23 18:14:57 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec_norm(t_vec3 *self)
{
	t_vec3	ret;
	double	len;

	len = 1. / vec_len(self);
	ret.e[0] = self->e[0] * len;
	ret.e[1] = self->e[1] * len;
	ret.e[2] = self->e[2] * len;
	return (ret);
}

double	vec_sin(t_vec3 *self, t_vec3 *other)
{
	double	cosine;

	cosine = vec_cos(self, other);
	return (sqrt(1 - cosine * cosine));
}

double	vec_cos(t_vec3 *self, t_vec3 *other)
{
	return (vec_dot(self, other) * 1. / (vec_len(self) * vec_len(other)));
}

double	vec_len(t_vec3 *self)
{
	return (sqrt(vec_len2(self)));
}
double	vec_len2(t_vec3 *self)
{
	return (self->e[0] * self->e[0]
		+ self->e[1] * self->e[1]
		+ self->e[2] * self->e[2]
	);
}
