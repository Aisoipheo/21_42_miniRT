/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:02:39 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:04 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "miniRT.h"
#include "get_next_line_bonus.h"
#include "utils.h"

int	next_word(char *line, int *wl, char **word)
{
	int	i;
	int	j;

	i = 0;
	*wl = 0;
	if (line == NULL)
		return (1);
	while (line && line[i] && line[i] == ' ')
		++i;
	while (line && line[i] && ((line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= 'A' && line[i] <= 'Z')))
		(*wl) += (++i || 1);
	*word = (char *)malloc(sizeof(char) * (*wl + 1));
	if (*word == NULL)
		return (-1);
	j = -1;
	while (++j < *wl)
		(*word)[j] = line[i - *wl + j];
	(*word)[*wl] = '\0';
	return (i);
}

int	parse_stage0(t_info *info, char *line, int len)
{
	int		wl;
	int		i;
	char	*word;

	if (line == NULL || len == 0)
		return (1);
	i = next_word(line, &wl, &word);
	if (i == -1)
		return (1);
	if (ft_strcmp(word, "C") == 0)
		return (parse_camera(info, line, word, i));
	if (ft_strcmp(word, "A") == 0)
		return (parse_ambient(info, line, word, i));
	if (ft_strcmp(word, "L") == 0)
		return (parse_light(info, line, word, i));
	if (ft_strcmp(word, "sp") == 0 || ft_strcmp(word, "Sp") == 0)
		return (parse_sphere(info, line, word, i));
	if (ft_strcmp(word, "cy") == 0 || ft_strcmp(word, "Cy") == 0)
		return (parse_cylinder(info, line, word, i));
	if (ft_strcmp(word, "pl") == 0 || ft_strcmp(word, "Pl") == 0)
		return (parse_plane(info, line, word, i));
	free(word);
	return (1);
}

int	rt_parse_map(t_info *info)
{
	char	*line;
	int		len;
	int		fd;

	line = NULL;
	fd = open(info->map, O_RDONLY);
	if (fd == -1)
		return (1);
	len = get_next_line(fd, &line);
	while (len > 0 && line)
	{
		parse_stage0(info, line, len);
		if (line)
			free(line);
		line = NULL;
		len = get_next_line(fd, &line);
	}
	if (line)
		free(line);
	return (close(fd));
}
