/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:16:30 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/18 15:11:50 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array.h"

t_obj_array	*obj_arr_new(t_uint size)
{
	t_obj_array	*arr;

	arr = (t_obj_array *)malloc(sizeof(t_obj_array));
	if (!arr || obj_arr_init(arr, size))
		return (NULL);
	return (arr);
}

int	obj_arr_init(t_obj_array *self, t_uint size)
{
	self->arr = (t_object *)malloc(sizeof(t_object) * size);
	if (!self->arr)
		return (obj_arr_free(self) == NULL);
	self->capacity = size;
	self->last = 0;
	return (0);
}

int	obj_arr_push(t_obj_array *self, t_object *obj)
{
	if (self->last >= self->capacity && obj_arr_realloc(self))
		return (1);
	self->arr[(self->last)++] = *obj;
	return (0);
}

int	obj_arr_realloc(t_obj_array *self)
{
	t_object	*tmp;
	t_uint		i;

	i = self->capacity;
	self->capacity <<= 1;
	++self->capacity;
	tmp = (t_object *)malloc(sizeof(t_object) * (self->capacity));
	if (!tmp)
		return (1);
	while (i--)
		tmp[i] = self->arr[i];
	free(self->arr);
	self->arr = tmp;
	return (0);
}

void	*obj_arr_free(t_obj_array *self)
{
	free(self->arr);
	free(self);
	return (NULL);
}
