/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:03:46 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/18 15:08:32 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include "object.h"

typedef unsigned int	t_uint;

typedef struct s_obj_array
{
	t_object	*arr;
	t_uint		capacity;
	t_uint		last;
}	t_obj_array;

typedef struct s_light_array
{
	t_light		*arr;
	t_uint		capacity;
	t_uint		last;
}	t_l_array;

t_obj_array		*obj_arr_new(t_uint size);
int			obj_arr_init(t_obj_array *self, t_uint size);
int			obj_arr_push(t_obj_array *self, t_object *obj);
int			obj_arr_realloc(t_obj_array *self);
void		*obj_arr_free(t_obj_array *self);

t_l_array		*l_arr_new(t_uint size);
int			l_arr_init(t_l_array *self, t_uint size);
int			l_arr_push(t_l_array *self, t_light *l);
int			l_arr_realloc(t_l_array *self);
void		*l_arr_free(t_l_array *self);

#endif
