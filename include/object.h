/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:04:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/09 19:03:31 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vec3.h"

# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYLINDER 3

// type
// position
// rotation / direction
// color
// light absorbtion [0; 1]

typedef struct s_object	t_object;
typedef struct s_ray	t_ray;
typedef struct s_hit	t_hit;

typedef double			(*t_object_hit_ptr)(t_object *, t_ray *,
	t_hit *, double cd);
typedef t_vec3			(*t_object_normal_ptr)(t_object *, t_hit *);

typedef struct s_object
{
	t_vec3				p;
	t_vec3				r;
	t_color				c;
	double				u[2];
	t_object_hit_ptr	hit;
	t_object_normal_ptr	norm;
	int					type;
}	t_object;

typedef struct s_light
{
	t_point3	p;
	t_color		c;
	double		b;
}	t_light;

// parameters for objects

// all objects
// lp[0] - light absorbation [0; 1]
// lp[1] - shininess [0; 1];

// PLANE
// NO PARAMS

// SPHERE
// u[0] - radius

// CYLINDER
// u[0] - diameter
// u[1] - height

// void	obj_copy(t_object *lhs, t_object *rhs);

#endif
