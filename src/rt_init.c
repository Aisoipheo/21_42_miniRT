/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:16 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/11 16:40:59 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "miniRT.h"

static int	rt_mlx_destroy(t_info *info)
{
	if (info->mlx && info->screen.img)
		mlx_destroy_image(info->mlx, info->screen.img);
	if (info->mlx && info->window)
		mlx_destroy_window(info->mlx, info->window);
	return (1);
}

static int	rt_mlx_init(t_info *info)
{
	info->mlx = mlx_init();
	info->window = mlx_new_window(info->mlx, info->w_window,
			info->h_window, RT_TITLE);
	info->screen.img = mlx_new_image(info->mlx, info->w_window, info->h_window);
	info->sky.img = mlx_xpm_file_to_image(info->mlx, "resources/sky/sky_map1.xpm", &info->sky.w, &info->sky.h);
	if (info->mlx == NULL || info->window == NULL || info->screen.img == 0 || info->sky.img == 0)
		return (1);
	info->screen.addr = mlx_get_data_addr(info->screen.img, &(info->screen.bpp),
			&(info->screen.size_line), &(info->screen.endian));
	info->sky.addr = mlx_get_data_addr(info->sky.img, &(info->sky.bpp),
			&(info->sky.size_line), &(info->sky.endian));
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->window, EVENT_DESTROY, MASK_NONE, rt_exit_hook, info);
	mlx_hook(info->window, EVENT_KEYPRESS, MASK_NONE, rt_keypress_hook, info);
	mlx_hook(info->window, EVENT_MPRESS, MASK_NONE, rt_mouse_hook, info);
	// mlx_loop_hook(info->mlx, rt_loop_hook, info);
	return (0);
}

static int	rt_prepare_scene(t_info *info)
{
	/* --> PARSE HERE! <-- (yes right in this line) */

	// setup camera (should be parsed)
	info->cam.orig = (t_vec3) {3, 0, 3};
	info->cam.dir = (t_vec3) {-1, 0, -1};
	info->fov = 180;

	// setup objects (should be parsed)
	t_object	obj;

	// //plane
	// obj.type = OBJ_PLANE;
	// obj.p = (t_vec3) {1000, 0, 0};
	// obj.r = (t_vec3) {1, 0, 0};
	// obj.c = (t_vec3) {0, 255, 255};
	// obj.a = 0;
	// obj.u[0] = 1;
	// obj.u[1] = 0;
	// obj.func = &rt_hit_plane;
	// arr_push(&(info->objs), &obj);

	// //plane
	// obj.type = OBJ_CYLINDER;
	// obj.p = (t_vec3) {0, 10, 0};
	// obj.r = (t_vec3) {1, 1, 0};
	// obj.c = (t_vec3) {128, 255, 255};
	// obj.a = 0;
	// obj.u[0] = 5;
	// obj.u[1] = 10;
	// obj.func = &rt_hit_cylinder;
	// arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {5, 0, 0};
	obj.r = (t_vec3) {1, 0, 0};
	obj.c = (t_vec3) {255, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);


	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {-5, 0, 5};
	obj.r = (t_vec3) {1, 0, 0};
	obj.c = (t_vec3) {255, 0, 255};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {5, 0, -5};
	obj.r = (t_vec3) {1, 0, 0};
	obj.c = (t_vec3) {255, 255, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, 0, 5};
	obj.r = (t_vec3) {0, 0, 1};
	obj.c = (t_vec3) {0, 255, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

/* GRAY COL */

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, 0, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -1, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {51, 51, 51};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -2, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {102, 102, 102};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -3, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {153, 153, 153};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -4, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {204, 204, 204};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -5, 0};
	obj.r = (t_vec3) {0, 1, 0};
	obj.c = (t_vec3) {255, 255, 255};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

/* END OF GRAY COL */
/* RED COL */

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, 0, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, -1, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {51, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, -2, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {102, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, -3, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {153, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, -4, 0};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {204, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {2.5, -5, 0};
	obj.r = (t_vec3) {0, 1, 0};
	obj.c = (t_vec3) {255, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

/* END OF RED COL */
/* GREEN COL */

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, 0, 2.5};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 0, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -1, 2.5};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 51, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -2, 2.5};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 102, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -3, 2.5};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 153, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -4, 2.5};
	obj.r = (t_vec3) {0, 0, 0};
	obj.c = (t_vec3) {0, 204, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	//sphere
	obj.type = OBJ_SPHERE;
	obj.p = (t_vec3) {0, -5, 2.5};
	obj.r = (t_vec3) {0, 1, 0};
	obj.c = (t_vec3) {0, 255, 0};
	obj.a = 0;
	obj.u[0] = 1;
	obj.u[1] = 0;
	obj.func = &rt_hit_sphere;
	arr_push(&(info->objs), &obj);

	printf("%u objs\n", info->objs.last);

	// find camera basis && normalize camera dir
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
	info->h_view = 9.0;
	info->w_view = RT_ASPECT_RATIO * info->h_view;
	info->w_view_2 = info->w_view / 2.0;
	info->h_view_2 = info->h_view / 2.0;
	// info->focal = info->w_view_2 * (1.0 / tan(info->fov * RT_DEG2RAD * 0.5));
	info->focal = NAN;

	info->theta = info->fov * info->one_w_windowm1 * RT_DEG2RAD;
	info->cost = cos(info->theta);
	info->sint = sin(info->theta);
	info->cost0 = cos(info->fov / 2.0 * RT_DEG2RAD);
	info->sint0 = sin(info->fov / 2.0 * RT_DEG2RAD);

	// info->gamma = atan(info->h_view_2 / info->w_view_2);
	info->gamma = info->fov / RT_ASPECT_RATIO / 2.0 * RT_DEG2RAD;
	info->cosg = cos(info->gamma * 2.0 * info->one_h_windowm1);
	info->sing = sin(info->gamma * 2.0 * info->one_h_windowm1);
	info->cosg0 = cos(info->gamma);
	info->sing0 = sin(info->gamma);

	printf("New cam basis:\n");
	printf("   %f    %f    %f\n", info->b.v[0].e[0], info->b.v[1].e[0], info->b.v[2].e[0]);
	printf("v0 %f v1 %f v2 %f\n", info->b.v[0].e[1], info->b.v[1].e[1], info->b.v[2].e[1]);
	printf("   %f    %f    %f\n", info->b.v[0].e[2], info->b.v[1].e[2], info->b.v[2].e[2]);
	printf("FOV: %f focal: %f\n", info->fov, info->focal);
	printf("theta: %f gamma: %f\n", info->fov, info->gamma * 2.0 / RT_DEG2RAD);
	printf("dtheta: %f dgamma: %f\n", info->theta / RT_DEG2RAD, info->gamma * 2.0 * info->one_h_windowm1 / RT_DEG2RAD);
	printf("cost0: %f sint0: %f cost: %f sint: %f\n", info->cost0, info->sint0, info->cost, info->sint);
	printf("cosg0: %f sing0: %f cosg: %f sing: %f\n", info->cosg0, info->sing0, info->cosg, info->sing);
	printf("\n");
	return (0);
}

int	rt_init(t_info *info)
{
	info->h_window = 9 * 75;
	info->w_window = 16 * 75;
	info->one_w_window = 1.0 / (double)info->w_window;
	info->one_h_window = 1.0 / (double)info->h_window;
	info->one_w_windowm1 = 1.0 / ((double)info->w_window - 1);
	info->one_h_windowm1 = 1.0 / ((double)info->h_window - 1);
	if (rt_mlx_init(info))
		return (rt_error(RT_ERR_INIT, 1));
	if (arr_init(&(info->objs), 0))
		return (rt_error(RT_ERR_INIT, 1));
	if (rt_prepare_scene(info))
		return (rt_error(RT_ERR_INIT, 1));
	return (0);
}

int	rt_destroy(t_info *info)
{
	free(info->objs.arr);
	rt_mlx_destroy(info);
	return (1);
}
