/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:16:30 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/29 16:03:17 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array.h"

t_array	*arr_new(t_uint size)
{
	t_array	*arr;

	arr = (t_array *)malloc(sizeof(t_array));
	if (!arr || arr_init(arr, size))
		return (NULL);
	return (arr);
}

int	arr_init(t_array *self, t_uint size)
{
	self->arr = (t_object *)malloc(sizeof(t_object) * size);
	if (!self->arr)
		return (arr_free(self) == NULL);
	self->capacity = size;
	self->last = 0;
	return (0);
}

int	arr_push(t_array *self, t_object *obj)
{
	if (self->last + 1 == self->capacity && arr_realloc(self))
		return (1);
	self->arr[(self->last)++] = *obj;
	return (0);
}

int	arr_realloc(t_array *self)
{
	t_object	*tmp;
	t_uint		i;

	tmp = (t_object *)malloc(sizeof(t_object) * (self->capacity << 1));
	if (!tmp)
		return (1);
	i = self->capacity;
	while (i--)
		tmp[i] = self->arr[i];
	self->capacity <<= 1;
	free(self->arr);
	self->arr = tmp;
	return (0);
}

void	*arr_free(t_array *self)
{
	free(self->arr);
	free(self);
	return (NULL);
}
