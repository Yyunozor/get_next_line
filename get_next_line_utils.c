/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:46:49 by anpayot           #+#    #+#             */
/*   Updated: 2024/12/10 18:15:05 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_next_line_utils.c
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return ((char)c == '\0' ? (char *)s : NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char    *joined;
	size_t  len1;
	size_t  len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	if (s1)
		ft_strlcpy(joined, s1, len1 + 1);
	else
		joined[0] = '\0';
	if (s2)
		ft_strlcpy(joined + len1, s2, len2 + 1);
	return (joined);
}

char	*ft_strjoin_free(char **s1, const char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return (*s1);
	len1 = *s1 ? ft_strlen(*s1) : 0;
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	if (*s1)
		ft_strlcpy(joined, *s1, len1 + 1);
	else
		joined[0] = '\0';
	ft_strlcpy(joined + len1, s2, len2 + 1);
	free(*s1);
	*s1 = joined;
	return (*s1);
}
