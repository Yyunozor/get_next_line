/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:46:34 by anpayot           #+#    #+#             */
/*   Updated: 2024/12/10 18:27:37 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*read_and_join(int fd, char *buffer)
{
	char	*read_buf;
	int		bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!buffer || !ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		read_buf[bytes_read] = '\0';
		if (!ft_strjoin_free(&buffer, read_buf))
		{
			free(read_buf);
			free(buffer); // Free buffer to prevent memory leak
			return (NULL);
		}
	}
	free(read_buf);
	if (bytes_read < 0)
	{
		free(buffer); // Free buffer in case of read error
		return (NULL);
	}
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp;
	size_t	len;

	if (!*buffer || !**buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	newline_pos = ft_strchr(*buffer, '\n');
	len = newline_pos ? (size_t)(newline_pos - *buffer + 1) : ft_strlen(*buffer);
	line = malloc(len + 1);
	if (!line)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	ft_strlcpy(line, *buffer, len + 1);
	if (newline_pos)
	{
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
		{
			free(line);
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		free(*buffer);
		if (*temp == '\0')
		{
			free(temp);
			*buffer = NULL;
		}
		else
		{
			*buffer = temp;
		}
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_join(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(&buffer);
	return (line);
}