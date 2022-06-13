/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:53:35 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:30:54 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"
#include "utils.h"

int	parse_plane2(char *line, t_object *o, int i)
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
	i += next_d(line + i, &d[2]);
	o->c = (t_vec3){d[0], d[1], d[2]};
	vec_norm_rgb(&o->c);
	return (0);
}

int	parse_plane(t_info *info, char *line, char *word, int i)
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
	if (ft_count_d(line + i) != 9)
	{
		free(os);
		free(o);
		free(word);
		return (1);
	}
	push_ll(&info->llo, os);
	o->type = OBJ_PLANE;
	o->hit = &rt_hit_plane_w;
	o->norm = &rt_norm_plane;
	return (parse_plane2(line, o, i));
}

int	parse_sphere2(char *line, t_object *o, int i)
{
	double	d[3];

	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	o->p = (t_vec3){d[0], d[1], d[2]};
	i += next_d(line + i, &d[0]);
	o->u[0] = d[0] * 0.5;
	o->r = (t_vec3){0, 0, 1};
	o->r = vec_norm(&o->r);
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	o->c = (t_vec3){d[0], d[1], d[2]};
	vec_norm_rgb(&o->c);
	return (0);
}

int	parse_sphere(t_info *info, char *line, char *word, int i)
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
	if (ft_count_d(line + i) != 7)
	{
		free(os);
		free(o);
		free(word);
		return (1);
	}
	push_ll(&info->llo, os);
	o->type = OBJ_SPHERE;
	o->hit = &rt_hit_sphere_w;
	o->norm = &rt_norm_sphere;
	return (parse_sphere2(line, o, i));
}

int	parse_light(t_info *info, char *line, char *word, int i)
{
	double	d[3];
	t_light	l;

	free(word);
	if (ft_count_d(line + i) != 7)
		return (1);
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	l.p = (t_vec3){d[0], d[1], d[2]};
	i += next_d(line + i, &d[0]);
	l.b = d[0];
	l.b = ft_dmax(l.b, 0.0);
	l.b = ft_dmin(l.b, 1.0);
	i += next_d(line + i, &d[0]);
	i += next_d(line + i, &d[1]);
	i += next_d(line + i, &d[2]);
	l.c = (t_vec3){d[0], d[1], d[2]};
	vec_norm_rgb(&l.c);
	l_arr_push(&info->lights, &l);
	return (0);
}
