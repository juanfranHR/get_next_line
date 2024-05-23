/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanhern <juanhern@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-13 13:21:41 by juanhern          #+#    #+#             */
/*   Updated: 2024-05-13 13:21:41 by juanhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char **extra, int fd)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while (extra[fd][i] && extra[fd][i] != '\n')
		i++;
	line = ft_substr(extra[fd], 0, i + 1);
	temp = ft_strdup(&extra[fd][i + 1]);
	free(extra[fd]);
	extra[fd] = temp;
	return (line);
}

static char	*return_line(char **extra, int fd, int bytes_read)
{
	char	*temp;

	if (bytes_read < 0 || extra[fd] == NULL || extra[fd][0] == '\0')
	{
		if (extra[fd] != NULL)
		{
			free(extra[fd]);
			extra[fd] = NULL;
		}
		return (NULL);
	}
	else if (ft_strchr(extra[fd], '\n') != NULL)
		return (get_line(extra, fd));
	else
	{
		temp = ft_strdup(extra[fd]);
		free(extra[fd]);
		extra[fd] = NULL;
		return (temp);
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*extra[4096];
	char		*temp;
	int			bytes_read;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		temp = ft_strjoin(extra[fd], buff);
		free(extra[fd]);
		extra[fd] = temp;
		if (ft_strchr(extra[fd], '\n'))
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (return_line(extra, fd, bytes_read));
}
