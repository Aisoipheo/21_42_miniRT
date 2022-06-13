/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:03:02 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 17:37:45 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
double	ft_dmax(const double d1, const double d2);
double	ft_dmin(const double d1, const double d2);
int		next_d(char *line, double *n);
int		ft_is_dchar(char c);
int		ft_isnum(char c);
int		ft_count_d(char *line);
int		ft_check_arg(char *arg);

#endif
