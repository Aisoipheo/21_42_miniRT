/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 17:19:23 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "array.h"
# include "mlx.h"
# include "mlx.h"

// [BEGIN] X11/X.h
# define MASK_NONE 0L

# define EVENT_KEYPRESS		2
# define EVENT_MPRESS		4
# define EVENT_MRELEASE		5
# define EVENT_ENTERWIN		7
# define EVENT_LEAVEWIN		8
# define EVENT_FOCUSIN		9
# define EVENT_FOCUSOUT		10
# define EVENT_VISIBLE		15
# define EVENT_DESTROY		17
// [END] X11/X.h

// [BEGIN] Keyboard
# define KEY_ESC		53
# define KEY_SPCE		49
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_UP			126
# define KEY_DOWN		125
# define KEY_I			34
# define KEY_D			2
# define KEY_A			0
# define KEY_S			1
# define KEY_W			13
// [END] Keyboard

// [BEGIN] Mouse
# define M_LMB		1
# define M_RMB		2
# define M_WUP		4
# define M_WDOWN	5
// [END] Mouse

# define RT_DEG2RAD 0.017453292519943295769236907684886127134428718885417254

# define RT_TITLE "miniRT"
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
	double		wh_ratio;
	void		*mlx;
	void		*window;
	void		*screen;
	char		*screen_addr;
	int			w_window;
	int			h_window;
	int			w_scale;
	int			h_scale;
	int			bpp;
	int			size_line;
	int			endian;
}	t_info;

void	rt_prepare_image(t_info *info);

int	rt_error(const char *msg, char is_lib);
int	rt_init(t_info *info);
int	rt_destroy(t_info *info);

int	rt_exit_hook(t_info *info);
int	rt_keypress_hook(int key, t_info *info);
// int	rt_mouse_hook(int key, int x, int y, t_info *info);
int	rt_loop_hook(t_info *info);
#endif
