/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:16 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 16:13:19 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"

int	rt_init(t_info *info)
{
	if (arr_init(&(info->objs), 0))
		return (rt_error(RT_ERR_INIT, 1));
	return (0);
}

int	rt_destroy(t_info *info)
{
	free(info->objs.arr);
	return (1);
}
