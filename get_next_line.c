/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanhern <juanhern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:32:59 by juanhern          #+#    #+#             */
/*   Updated: 2024/04/28 12:01:58 by juanhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char **extra)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*extra)[i] && (*extra)[i] != '\n')
		i++;
	if (!ft_strchr(*extra, '\n'))
	{
		line = ft_strdup(*extra);
		free(*extra);
		*extra = NULL;
	}
	else
	{
		line = ft_substr((*extra), 0, i + 1);
		temp = ft_strdup(&(*extra)[i + 1]);
		free(*extra);
		*extra = temp;
	}
	return (line);
}

static char	*return_line(char **extra, int bytes_read)
{
	if (bytes_read < 0 || *extra == NULL || *extra[0] == '\0')
	{
		if (*extra != NULL)
		{
			free(*extra);
			*extra = NULL;
		}
		return (NULL);
	}
	else
		return (get_line(extra));
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*extra;
	char		*temp;
	int			bytes_read;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE < 0 || BUFFER_SIZE > __INT_MAX__)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		temp = ft_strjoin(extra, buff);
		free(extra);
		extra = temp;
		if (ft_strchr(extra, '\n'))
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (return_line(&extra, bytes_read));
}
