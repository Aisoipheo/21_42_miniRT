/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ll_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:26 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:13:52 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"

t_ll_objs	*new_ll(t_object *obj, char *word)
{
	t_ll_objs	*o;

	o = (t_ll_objs *)malloc(sizeof(t_ll_objs));
	if (o == NULL)
		return (NULL);
	o->word = word;
	o->obj = obj;
	o->next = NULL;
	return (o);
}

void	free_ll(t_ll_objs *ll)
{
	t_ll_objs	*ptr;

	while (ll)
	{
		ptr = ll->next;
		free(ll->word);
		free(ll->obj);
		free(ll);
		ll = ptr;
	}
}

void	push_ll(t_ll_objs **ll, t_ll_objs *nll)
{
	t_ll_objs	*ptr;

	if (*ll == NULL)
	{
		*ll = nll;
		return ;
	}
	ptr = *ll;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = nll;
}
