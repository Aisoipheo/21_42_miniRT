/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:23:17 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:33:25 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rt_rt_f_2(t_info *info, t_ray *r, t_hit *h, int i)
{
	r[0].dir = (t_vec3){info->lights.arr[i].p.e[0] - h->p.e[0],
		info->lights.arr[i].p.e[1] - h->p.e[1],
		info->lights.arr[i].p.e[2] - h->p.e[2]};
	r[2].dir = vec_norm(&r[0].dir);
}

void	rt_rt_f_3(t_info *info, t_ray *r, t_ray *view_ray, t_uint objno)
{
	if (info->objs.arr[objno].type == OBJ_PLANE
		&& vec_dot(&r[1].dir, &(view_ray->dir)) > 0)
		r[1].dir = vec_neg(&r[1].dir);
}
