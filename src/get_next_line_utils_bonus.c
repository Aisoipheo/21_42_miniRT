/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:54:36 by rdrizzle          #+#    #+#             */
/*   Updated: 2021/05/14 14:17:15 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

t_gnl_list	*new_gnl_list_elem(int fd)
{
	t_gnl_list	*elem;

	elem = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (elem)
	{
		elem->fd = fd;
		elem->next = NULL;
		elem->str = NULL;
	}
	return (elem);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ptr;
	char	*ptr1;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str)
	{
		ptr = str;
		ptr1 = s1;
		while (s1 && *s1)
			*ptr++ = *s1++;
		if (ptr1)
			free(ptr1);
		while (s2 && *s2)
			*ptr++ = *s2++;
		*ptr = '\0';
	}
	return (str);
}

int	ft_slice(char *src, char **before, char **after)
{
	char	*ptr;
	ssize_t	at;

	if (src)
	{
		at = ft_contains(src, '\n');
		ptr = NULL;
		if (at > -1)
			src[at] = '\0';
		*before = ft_strdup(src);
		if (!*before)
			return (-1);
		if (at > -1)
		{
			src += at + 1;
			ptr = ft_strdup(src);
			if (!ptr)
				return (-1);
		}
		free(*after);
		*after = ptr;
		return (at > -1);
	}
	return (-1);
}

void	delete_gnl_list_elem(t_gnl_list **gnl_list, t_gnl_list *target)
{
	t_gnl_list	*ptr;

	if (gnl_list && *gnl_list)
	{
		if ((*gnl_list) == target)
		{
			free((*gnl_list)->str);
			ptr = (*gnl_list)->next;
			free(*gnl_list);
			*gnl_list = ptr;
		}
		else
		{
			ptr = *gnl_list;
			while (ptr->next != target)
				ptr = ptr->next;
			ptr->next = ptr->next->next;
			free(target->str);
			free(target);
		}
	}
}

int	read_until_nl(int fd, t_gnl_list *handler, char **line)
{
	ssize_t	rr;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	rr = -1;
	while (buf)
	{
		rr = read(fd, buf, BUFFER_SIZE);
		if (rr < 0)
			break ;
		buf[rr] = '\0';
		handler->str = ft_strjoin(handler->str, buf);
		if (rr == 0 || (ft_contains(buf, '\n') > -1))
		{
			rr = ft_slice(handler->str, line, &handler->str);
			break ;
		}
	}
	free(buf);
	return (rr);
}
