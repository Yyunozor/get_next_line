/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:46:34 by anpayot           #+#    #+#             */
/*   Updated: 2024/12/12 09:13:36 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	char	*ptr;
	char	*buf_ptr;
	size_t	len;

	if (!buffer || !*buffer)
		return (NULL);
	buf_ptr = buffer;
	while (*buf_ptr && *buf_ptr != '\n')
		buf_ptr++;
	len = buf_ptr - buffer;
	if (*buf_ptr == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ptr = line;
	while (buffer != buf_ptr)
		*ptr++ = *buffer++;
	if (*buffer == '\n')
		*ptr++ = '\n';
	*ptr = '\0';
	return (line);
}

static char	*create_new_buffer(char *buffer, char *newline_pos)
{
	char	*new_buf;
	char	*ptr;

	new_buf = malloc(ft_strlen(newline_pos));
	if (!new_buf)
		return (free_null(buffer));
	ptr = new_buf;
	newline_pos++;
	while (*newline_pos)
		*ptr++ = *newline_pos++;
	*ptr = '\0';
	free(buffer);
	return (new_buf);
}

static char	*update_buffer(char *buffer)
{
	char	*ptr;

	if (!buffer)
		return (NULL);
	ptr = buffer;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (!*ptr)
		return (free_null(buffer));
	return (create_new_buffer(buffer, ptr));
}

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp;
	int		read_bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free_null(buffer));
	read_bytes = 1;
	while (!ft_strchr(buffer, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(temp);
			return (free_null(buffer));
		}
		temp[read_bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_from_buffer(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
