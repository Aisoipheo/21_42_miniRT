/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_prepare_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:13:23 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/27 17:25:38 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "miniRT.h"
#include "benchmark.h"

inline void	pixel_put(t_info *info, t_color *color, int x, int y)
{
	char	*dst;

	dst = info->screen_addr + y * info->size_line + (x * info->bpp / 8);
	*(unsigned int *)dst = (((int)color->e[0]) << 16) | (((int)color->e[1]) << 8)
		| (((int)color->e[2]));
}

inline void	get_color(t_info *info, t_color *c, t_uint x, t_uint y)
{
	c->e[0] = 255.999 * ((double)x * 1.0 / (double)info->w_window);
	c->e[1] = 255.999 * ((double)y * 1.0 / (double)info->h_window);
	c->e[2] = 255.999 * 0.25;
}

void	rt_prepare_image(t_info *info)
{
	t_uint	i;
	t_uint	j;
	t_color	c;
	t_ull	start;
	t_ull	end;
//	t_ray ?
//	t_hit ?

	i = info->h_window;

	printf("Rendering...\n");
	start = clock_now_usec();
	while (i--)
	{
		j = info->w_window;
		while(j--)
		{
			get_color(info, &c, j, i);
			pixel_put(info, &c, j, i);
		}
		printf("\r%f",(1.0 - (double)i / info->h_window) * 100.0);
		fflush(stdout);
	}
	end = clock_now_usec();
	printf("\nReady!\n");
	print_time_usec(end - start);
}
