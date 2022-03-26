/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 15:34:42 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "array.h"

# define RT_DEG_TO_RAD 0.017453292519943295769236907684886127134428718885417254

# define RT_ERR_INIT "miniRT initialization failed"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
}	t_camera;


typedef struct s_info
{
	t_array		objs;
	t_camera	cam;
}	t_info;

double	rt_deg_to_rad(double deg);

int	rt_error(const char *msg, char is_lib);
int	rt_init(t_info *info);
int	rt_destroy(t_info *info);

#endif
