/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:54:06 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/10 18:18:29 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static t_gnl_list	*gnl_list = NULL;
	t_gnl_list			*handler;
	int					ret;

	if ((fd < 0) || (NULL == line) || (BUFFER_SIZE <= 0))
		return (-1);
	handler = gnl_list_get_fd_handler(&gnl_list, fd);
	if (!handler)
		return (-1);
	ret = read_until_nl(fd, handler, line);
	if (ret < 1)
		delete_gnl_list_elem(&gnl_list, handler);
	return (ret);
}

char	*ft_strdup(char *s)
{
	char	*res;
	char	*ptr;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	ptr = res;
	while (s && *s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (res);
}

// size_t	ft_strlen(char *s)
// {
// 	size_t	res;

// 	res = 0;
// 	while (s && *s)
// 		res += (s++ || 1);
// 	return (res);
// }

ssize_t	ft_contains(char *s, char c)
{
	ssize_t	res;

	if (s)
	{
		res = 0;
		while (*s)
		{
			if (*s == c)
				return (res);
			res += (s++ || 1);
		}
	}
	return (-1);
}

t_gnl_list	*gnl_list_get_fd_handler(t_gnl_list **gnl_list, int fd)
{
	t_gnl_list	*ptr;

	if (gnl_list)
	{
		if (*gnl_list)
		{
			ptr = *gnl_list;
			while (ptr->next)
			{
				if (ptr->fd == fd)
					return (ptr);
				ptr = ptr->next;
			}
			if (ptr->fd == fd)
				return (ptr);
			ptr->next = new_gnl_list_elem(fd);
			return (ptr->next);
		}
		*gnl_list = new_gnl_list_elem(fd);
		return (*gnl_list);
	}
	return (NULL);
}
