/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:19 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 16:06:18 by rdrizzle         ###   ########.fr       */
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
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (is_lib)
		perror(strerror(errno));
	else
		write(STDERR_FILENO, "\n", 1);
	return (1);
}
