/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:46:34 by anpayot           #+#    #+#             */
/*   Updated: 2024/12/18 12:42:05 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	char	*ptr;
	char	*buffer_ptr;
	size_t	len;

	if (!buffer || !*buffer)
		return (NULL);
	buffer_ptr = buffer;
	while (*buffer_ptr && *buffer_ptr != '\n')
		buffer_ptr++;
	len = buffer_ptr - buffer;
	if (*buffer_ptr == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ptr = line;
	while (buffer != buffer_ptr)
		*ptr++ = *buffer++;
	if (*buffer == '\n')
		*ptr++ = '\n';
	*ptr = '\0';
	return (line);
}

static char	*create_new_buffer(char *buffer, char *newline_pos)
{
	char	*new_buffer;
	char	*ptr;

	new_buffer = malloc(ft_strlen(newline_pos));
	if (!new_buffer)
		return (free_null(buffer));
	ptr = new_buffer;
	newline_pos++;
	while (*newline_pos)
		*ptr++ = *newline_pos++;
	*ptr = '\0';
	free(buffer);
	return (new_buffer);
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
