/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:13:02 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/23 17:42:50 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct s_vec3
{
	double	e[3];
}	t_vec3;

typedef	t_vec3	t_point3;
typedef	t_vec3	t_color;

t_vec3		vec_zero(void);
t_vec3		vec_neg(t_vec3 *self);
t_vec3		*vec_add(t_vec3 *self, t_vec3 *other);
t_vec3		*vec_sub(t_vec3 *self, t_vec3 *other);
t_vec3		*vec_mul(t_vec3 *self, double t);
t_vec3		vec_norm(t_vec3 *self);
double		vec_sin(t_vec3 *self, t_vec3 *other);
double		vec_cos(t_vec3 *self, t_vec3 *other);
double		vec_len(t_vec3 *self);
double		vec_len2(t_vec3 *self);
double		vec_dot(t_vec3 *self, t_vec3 *other);
t_vec3		*vec_cross(t_vec3 *self, t_vec3 *other);
void		vec_copy(t_vec3 *self, t_vec3 *other);

#endif
