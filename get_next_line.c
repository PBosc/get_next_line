/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:18:46 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/11 16:18:46 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_first_line(char *str)
{
	char	*line;
	int		i;
	
	i = 0;	
	if (!save || save[0] == 0)
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
		line[i++] = str[i];
	line[i] = 0;
	return (line);
}

char		*get_end(char *str)
{
	int		i;
	char	*end;
	char	*tmp;
	
	i = 0;
	tmp = ft_strchr(str, '\n');
	if (!tmp)
	{
		free(str);
		return (NULL);	
	}
	while (str[i] && str[i] != '\n')
		i++;
	end = malloc(ft_strlen(str) - i)
	if (!end)
		return (NULL);
	tmp++;
	i = 0;
	while(*tmp)
		end[i++] = tmp++
	end[i] = 0;
	free(str);
	return (end);
}

static char	*read_line(char *save, int fd)
{
	char	*buf;
	char	*tmp;
	int		ret;
	
	ret = 1;
	buf = ft_calloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ret > 0 && !ft_strchr(buf, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf)
			return (NULL);
		}
		buf[ret] = 0;
		if (!save)
			save = ft_calloc(1,1);
		if (!save)
			return (NULL);
		tmp = save;
		save = ft_strjoin(save, buf)
		free(tmp);
		if (ft_strchr(save, '\n'))
			break;
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save = read_line(save, fd)
	if (!save)
		return (NULL);
	line = get_first_line(save);
	save = get_end(save);
	return (line);
}