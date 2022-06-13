/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:02:50 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:30:30 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

inline int	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}

inline double	ft_dmax(const double d1, const double d2)
{
	if (d1 > d2)
		return (d1);
	return (d2);
}

inline double	ft_dmin(const double d1, const double d2)
{
	if (d1 > d2)
		return (d2);
	return (d1);
}

inline int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
		s1 += (++s2 || 1);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	next_d(char *line, double *n)
{
	double	d[2];
	int		k[3];

	k[0] = 0;
	d[0] = 0;
	d[1] = 0;
	k[2] = 10.0;
	while (line && line[k[0]] && !ft_is_dchar(line[k[0]]))
		++k[0];
	k[1] = line[k[0]] == '-';
	k[0] += (line[k[0]] == '-' || line[k[0]] == '+');
	while (line[k[0]] && ft_isnum(line[k[0]]))
		d[0] = d[0] * 10.0 + line[k[0]++] - 48.0;
	k[0] += (line[k[0]] == '.');
	while (line[k[0]] && ft_isnum(line[k[0]]))
	{
		d[1] += (line[k[0]++] - 48.0) / k[2];
		k[2] *= 10.0;
	}
	*n = (d[0] + d[1]);
	if (k[1])
		*n = (-(d[0] + d[1]));
	return (k[0]);
}
