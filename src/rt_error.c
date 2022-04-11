/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:19 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/04/09 15:18:07 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "miniRT.h"
#include "utils.h"

int	rt_error(const char *msg, char is_lib)
{
	if (is_lib)
		perror(msg);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	return (1);
}
