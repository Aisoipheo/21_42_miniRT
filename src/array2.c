/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:10:20 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/18 15:12:36 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array.h"

t_l_array	*l_arr_new(t_uint size)
{
	t_l_array	*arr;

	arr = (t_l_array *)malloc(sizeof(t_l_array));
	if (!arr || l_arr_init(arr, size))
		return (NULL);
	return (arr);
}

int	l_arr_init(t_l_array *self, t_uint size)
{
	self->arr = (t_light *)malloc(sizeof(t_light) * size);
	if (!self->arr)
		return (l_arr_free(self) == NULL);
	self->capacity = size;
	self->last = 0;
	return (0);
}

int	l_arr_push(t_l_array *self, t_light *obj)
{
	if (self->last >= self->capacity && l_arr_realloc(self))
		return (1);
	self->arr[(self->last)++] = *obj;
	return (0);
}

int	l_arr_realloc(t_l_array *self)
{
	t_light		*tmp;
	t_uint		i;

	i = self->capacity;
	self->capacity <<= 1;
	++self->capacity;
	tmp = (t_light *)malloc(sizeof(t_light) * (self->capacity));
	if (!tmp)
		return (1);
	while (i--)
		tmp[i] = self->arr[i];
	free(self->arr);
	self->arr = tmp;
	return (0);
}

void	*l_arr_free(t_l_array *self)
{
	free(self->arr);
	free(self);
	return (NULL);
}
