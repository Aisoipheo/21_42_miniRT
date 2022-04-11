/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:28:43 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/11 16:32:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline double	closest_object(t_info *info, t_ray *r, t_uint hitno)
{
	t_uint	i;
	double	d;
	double	cd;

	cd = -1;
	i = 0;
	while (i != info->objs.last)
	{
		d = (info->objs.arr[i]).func(&(info->objs.arr[i]), r);
		if (cd != -1 && d != -1)
		{
			if (d < cd)
			{
				cd = d;
				info->hits[hitno] = i;
			}
		}
		else if (d != -1)
		{
			cd = d;
			info->hits[hitno] = i;
		}
		++i;
	}
	return (cd);
}

inline void	rt_raytrace(t_info *info, t_ray *r, t_color *c)
{
	t_uint	hits;
	double	d;

	hits = 0;
	d = -1;
	while (hits != RT_MAX_BOUNCE)
	{
		d = closest_object(info, r, hits);
		if (d == -1)
			rt_sky_color(info, r, c);
		else
			*c = info->objs.arr[info->hits[hits]].c;
		break;
		++hits;
	}
}
