/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:06:42 by lbagg             #+#    #+#             */
/*   Updated: 2020/06/10 11:40:12 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*news;
	size_t	i;

	i = ft_strlen(s);
	if (!(news = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		news[i] = s[i];
		i++;
	}
	news[i] = '\0';
	return (news);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(join = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
	* sizeof(char))))
		return (NULL);
	while (*s1)
	{
		join[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		join[i] = *s2++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	if (size != 0)
	{
		if (srclen >= size)
		{
			dst[size - 1] = '\0';
			size--;
			while (size-- > 0)
				dst[size] = src[size];
		}
		else
		{
			srclen++;
			while (srclen-- > 0)
				dst[srclen] = src[srclen];
		}
	}
	return (srclen);
}
