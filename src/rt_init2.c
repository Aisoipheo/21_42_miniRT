/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:35:02 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:17:09 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "miniRT.h"

static void	f_1(t_info *info)
{
	info->theta = info->fov * info->one_w_windowm1 * RT_DEG2RAD;
	info->cost = cos(info->theta);
	info->sint = sin(info->theta);
	info->cost0 = cos(info->fov / 2.0 * RT_DEG2RAD);
	info->sint0 = sin(info->fov / 2.0 * RT_DEG2RAD);
	info->gamma = info->fov / RT_ASPECT_RATIO / 2.0 * RT_DEG2RAD;
	info->cosg = cos(info->gamma * 2.0 * info->one_h_windowm1);
	info->sing = sin(info->gamma * 2.0 * info->one_h_windowm1);
	info->cosg0 = cos(info->gamma);
	info->sing0 = sin(info->gamma);
}

void	rt_calculate_camera(t_info *info)
{
	info->b.v[0] = (t_vec3){-info->cam.dir.e[2], 0, info->cam.dir.e[0]};
	if (info->cam.dir.e[0] == 0.0 && info->cam.dir.e[2] == 0.0)
	{
		printf("Bad camera direction! assuming rotation angle = 0\n");
		info->b.v[0] = (t_vec3){info->cam.dir.e[1], 0, 0};
	}
	info->b.v[1] = info->cam.dir;
	vec_cross(&(info->b.v[1]), &(info->b.v[0]));
	if (info->b.v[1].e[1] < 0)
	{
		info->b.v[0] = vec_neg(&(info->b.v[0]));
		info->b.v[1] = vec_neg(&(info->b.v[1]));
	}
	info->b.v[2] = info->cam.dir;
	info->b.v[0] = vec_norm(&(info->b.v[0]));
	info->b.v[1] = vec_norm(&(info->b.v[1]));
	info->b.v[2] = vec_norm(&(info->b.v[2]));
	info->cam.dir = vec_norm(&(info->cam.dir));
	f_1(info);
}

int	rt_check_map(t_info *info)
{
	return ((info->prs_flags & 0b11) != 0b11 || info->fov > 180
		|| info->fov < 0);
}

void	rt_select_objs2(t_info *info, int f)
{
	t_ll_objs	*ptr;

	ptr = info->llo;
	while (ptr)
	{
		if ((ft_strcmp(ptr->word, "cy") == 0 && ((f & 0b1) == 0))
			|| (ft_strcmp(ptr->word, "pl") == 0 && ((f & 0b10) == 0))
			|| (ft_strcmp(ptr->word, "sp") == 0 && ((f & 0b100) == 0))
			|| (ft_strcmp(ptr->word, "Cy") == 0
				&& (f & 0b1) && ((f & 0x8) == 0))
			|| (ft_strcmp(ptr->word, "Pl") == 0
				&& (f & 0b10) && ((f & 0x10) == 0))
			|| (ft_strcmp(ptr->word, "Sp") == 0
				&& (f & 0b100) && ((f & 0x20) == 0))
		)
			obj_arr_push(&info->objs, ptr->obj);
		if (ft_strcmp(ptr->word, "Cy") == 0 && (f & 0b1) && ((f & 0x8) == 0))
			f |= 0b1000;
		if (ft_strcmp(ptr->word, "Pl") == 0 && (f & 0b10) && ((f & 0x10) == 0))
			f |= 0b10000;
		if (ft_strcmp(ptr->word, "Sp") == 0 && (f & 0b100) && ((f & 0x20) == 0))
			f |= 0b100000;
		ptr = ptr->next;
	}
}

void	rt_select_objs(t_info *info)
{
	t_ll_objs	*ptr;
	int			f;

	f = 0;
	ptr = info->llo;
	while (ptr)
	{
		if (ft_strcmp(ptr->word, "Cy") == 0)
			f |= 0b1;
		if (ft_strcmp(ptr->word, "Pl") == 0)
			f |= 0b10;
		if (ft_strcmp(ptr->word, "Sp") == 0)
			f |= 0b100;
		ptr = ptr->next;
	}
	rt_select_objs2(info, f);
}
