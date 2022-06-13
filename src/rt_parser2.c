/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:33:51 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:30:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"
#include "utils.h"

int	parse_camera(t_info *info, char *line, char *word, int i)
{
	double	d[3];

	free(word);
	if (ft_count_d(line + i) != 7)
		return (1);
	info->prs_flags |= 0b1;
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	info->cam.orig = (t_vec3){d[0], d[1], d[2]};
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	info->cam.dir = (t_vec3){d[0], d[1], d[2]};
	info->cam.dir = vec_norm(&info->cam.dir);
	i += next_d(line + i, &d[0]);
	info->fov = d[0];
	return (0);
}

int	parse_ambient(t_info *info, char *line, char *word, int i)
{
	double	d[3];

	free(word);
	if (ft_count_d(line + i) != 4)
		return (1);
	info->prs_flags |= 0b10;
	i += next_d(line + i, &d[0]);
	info->amb_intencity = d[0];
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	info->amb_color = (t_vec3){d[0], d[1], d[2]};
	vec_norm_rgb(&info->amb_color);
	return (0);
}

int	parse_cylinder2(char *line, t_object *o, int i)
{
	double	d[3];

	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	o->p = (t_vec3){d[0], d[1], d[2]};
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	o->r = (t_vec3){d[0], d[1], d[2]};
	o->r = vec_norm(&o->r);
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	o->u[0] = d[0] * 0.5;
	o->u[1] = d[1] * 0.5;
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	o->c = (t_vec3){d[0], d[1], d[2]};
	vec_norm_rgb(&o->c);
	return (0);
}

int	parse_cylinder(t_info *info, char *line, char *word, int i)
{
	t_ll_objs	*os;
	t_object	*o;

	o = (t_object *)malloc(sizeof(t_object));
	if (o == NULL)
		return (1);
	os = new_ll(o, word);
	if (os == NULL)
	{
		free(o);
		free(word);
		return (1);
	}
	if (ft_count_d(line + i) != 11)
	{
		free(os);
		free(o);
		free(word);
		return (1);
	}
	push_ll(&info->llo, os);
	o->type = OBJ_CYLINDER;
	o->hit = &rt_hit_cylinder_w;
	o->norm = &rt_norm_cylinder;
	return (parse_cylinder2(line, o, i));
}
