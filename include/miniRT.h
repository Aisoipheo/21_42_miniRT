/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:44 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/16 17:19:26 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "array.h"
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
# define RT_RAY_DEN 16U
# define RT_COLOR_SCALE 0.0625
# define RT_ASPECT_RATIO 1.77777777777777777777777777777777777777777777777777778
# define RT_EPS 1e-8
# define RT_MAX_BOUNCE 32U

# define RT_TITLE "miniRT"
# define RT_ERR_INIT "miniRT initialization failed"

typedef struct s_hit
{
	t_vec3	p; // point of intersection
	double	d; // distance from ray origin to point of intersection
}	t_hit;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef t_ray	t_camera;

typedef struct s_basis3
{
	t_vec3	v[3];
}	t_basis3;

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx_img;

typedef struct s_info
{
	t_array		objs;
	t_camera	cam;
	t_basis3	b;
	t_vec3		rbc;
	double		theta;
	double		cost0;
	double		sint0;
	double		cost;
	double		sint;
	double		gamma;
	double		cosg;
	double		sing;
	double		cosg0;
	double		sing0;
	double		w_view;
	double		h_view;
	double		w_view_2;
	double		h_view_2;
	double		fov;
	double		focal;
	double		one_w_window;
	double		one_h_window;
	double		one_w_windowm1;
	double		one_h_windowm1;
	void		*mlx;
	void		*window;
	t_uint		hits[RT_MAX_BOUNCE];
	t_mlx_img	screen;
	t_mlx_img	sky;
	int			w_window;
	int			h_window;
}	t_info;

void	rt_render_image(t_info *info);
void	rt_sky_color(t_info *info, t_ray *r, t_color *c);
void	rt_raytrace(t_info *info, t_ray *r, t_color *c);

int		rt_error(const char *msg, char is_lib);
int		rt_init(t_info *info);
int		rt_destroy(t_info *info);

int		rt_exit_hook(t_info *info);
int		rt_keypress_hook(int key, t_info *info);
int		rt_mouse_hook(int key, int x, int y, t_info *info);
int		rt_loop_hook(t_info *info);

double		rt_solve(double *pc);
double		_rt_hit_cylinder(t_object *self, t_ray *r);
double		_rt_hit_cylinder_cap(t_object *self, t_ray *r);
double		rt_hit_plane(t_object *self, t_ray *r);
double		rt_hit_sphere(t_object *self, t_ray *r);
double		rt_hit_cylinder(t_object *self, t_ray *r);

#endif
