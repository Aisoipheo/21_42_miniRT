/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:02:50 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/26 16:04:33 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}
