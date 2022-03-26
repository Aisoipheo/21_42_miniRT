/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:43:20 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 14:45:55 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	obj_copy(t_object *lhs, t_object *rhs)
{
	lhs->type = rhs->type;
	vec_copy(&(lhs->p), &(rhs->p));
	vec_copy(&(lhs->c), &(rhs->c));
	vec_copy(&(lhs->r), &(rhs->r));
	lhs->a = rhs->a;
}
