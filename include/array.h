/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:03:46 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 17:57:13 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include "object.h"

typedef unsigned int	t_uint;

typedef struct s_array
{
	t_object	*arr;
	t_uint		capacity;
	t_uint		last;
}	t_array;

t_array		*arr_new(t_uint size);
int			arr_init(t_array *self, t_uint size);
int			arr_push(t_array *self, t_object *obj);
int			arr_realloc(t_array *self);
void		*arr_free(t_array *self);

#endif
