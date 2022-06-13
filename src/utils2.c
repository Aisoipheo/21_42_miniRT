/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:55:56 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 17:35:52 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_is_dchar(char c)
{
	return (c == '.' || c == '+' || c == '-'
		|| (c >= '0' && c <= '9'));
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_count_d(char *line)
{
	int		k[4];

	k[0] = 0;
	k[2] = 0;
	while (line[k[0]])
	{
		while (line[k[0]] && !ft_is_dchar(line[k[0]]))
			++k[0];
		k[1] = line[k[0]] == '-';
		k[0] += (line[k[0]] == '-' || line[k[0]] == '+');
		k[3] = ft_isnum(line[k[0]]);
		while (line[k[0]] && ft_isnum(line[k[0]]))
			++k[0];
		k[0] += (line[k[0]] == '.');
		k[3] = ft_isnum(line[k[0]]) | k[3];
		while (line[k[0]] && ft_isnum(line[k[0]]))
			++k[0];
		k[2] += k[3];
	}
	return (k[2]);
}

int	ft_check_arg(char *arg)
{
	int	l;

	l = ft_strlen(arg);
	return (!(l > 3 && arg[l - 1] == 't' && arg[l - 2] == 'r'
			&& arg[l - 3] == '.'));
}
