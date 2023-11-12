/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:26:14 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/12 17:34:45 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_first_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || str[0] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i])
		line[i] = str[i];
	line[i + (str[i] == '\n')] = 0;
	return (line);
}

char	*get_end(char *str)
{
	int		i;
	char	*end;
	char	*tmp;

	i = 0;
	tmp = ft_strchr(str, '\n');
	if (!tmp)
		return (free(str), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	end = malloc(ft_strlen(str) - i);
	if (!end)
		return (NULL);
	tmp++;
	i = 0;
	while (*tmp)
		end[i++] = *tmp++;
	end[i] = 0;
	return (free(str), end);
}

static char	*read_line(char *save, int fd)
{
	char	*buf;
	char	*tmp;
	int		ret;

	ret = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	while (ret > 0 && !ft_strchr(buf, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (free(buf), NULL);
		buf[ret] = 0;
		if (!save)
			save = ft_calloc(1, 1);
		if (!save)
			return (NULL);
		tmp = save;
		save = ft_strjoin(save, buf);
		free(tmp);
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (free(buf), save);
}

char	*get_next_line(int fd)
{
	static char	*save[4096];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save[fd] = read_line(save[fd], fd);
	if (!save[fd])
		return (NULL);
	line = get_first_line(save[fd]);
	save[fd] = get_end(save[fd]);
	return (line);
}
