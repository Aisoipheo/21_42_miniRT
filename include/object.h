/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:04:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/05 16:22:39 by rdrizzle         ###   ########.fr       */
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

typedef double	(*t_object_hit_ptr)(t_object *, t_ray *);

typedef struct s_object
{
	t_vec3				p; // position
	t_vec3				r; // rotation
	t_color				c; // color
	double				a; // light absorbtion
	double				u[2]; // parameters
	t_object_hit_ptr	func;
	int					type;
}	t_object;

// parameters for objects

// PLANE
// NO PARAMS

// SPHERE
// u[0] - radius

// CYLINDER
// u[0] - diameter
// u[1] - height


// void	obj_copy(t_object *lhs, t_object *rhs);

#endif
