/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:54:54 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/09 19:36:40 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <sys/types.h>
# include "utils.h"

int				get_next_line(int fd, char **line);
char			*ft_strdup(char *s);
// size_t			ft_strlen(char *s);
ssize_t			ft_contains(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_slice(char *src, char **before, char **after);

typedef struct s_gnl_list
{
	struct s_gnl_list	*next;
	char				*str;
	int					fd;
}				t_gnl_list;

t_gnl_list		*gnl_list_get_fd_handler(t_gnl_list **gnl_list, int fd);
t_gnl_list		*new_gnl_list_elem(int fd);
void			delete_gnl_list_elem(t_gnl_list **gnl_list, t_gnl_list *target);
int				read_until_nl(int fd, t_gnl_list *handler, char **line);
#endif
