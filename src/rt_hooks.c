/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:23:21 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 16:48:47 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"

int	rt_exit_hook(t_info *info)
{
	rt_destroy(info);
	exit(EXIT_SUCCESS);
}

int	rt_keypress_hook(int key, t_info *info)
{
	if (key == KEY_ESC)
		rt_exit_hook(info);
	return (0);
}

// int	rt_mouse_hook(int key, int x, int y, t_info *info);

int	rt_loop_hook(t_info *info)
{
	(void)info;
	return (0);
}
