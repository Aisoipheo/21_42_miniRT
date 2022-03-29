/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:04:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/29 19:11:05 by rdrizzle         ###   ########.fr       */
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

typedef struct s_object
{
	int				type;
	t_vec3			p; // position
	t_vec3			r; // rotation
	t_color			c; // color
	double			a; // light absorbtion
	double			u[2]; // parameters
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
