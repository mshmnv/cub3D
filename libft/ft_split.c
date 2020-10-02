/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:28:14 by lbagg             #+#    #+#             */
/*   Updated: 2020/05/16 16:32:28 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_letters(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*ft_nextword(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char*)s);
}

static size_t	ft_words(const char *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		words++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

static char		**ft_malloc_error(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	size_t	word;
	size_t	nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_words(s, c);
	if (!(res = ft_calloc(nb_words + 1, sizeof(char*))))
		return (NULL);
	word = 0;
	while (nb_words - word)
	{
		s = ft_nextword(s, c);
		if (!(res[word] = ft_substr(s, 0, ft_letters(s, c))))
			return (ft_malloc_error(res));
		word++;
		s += ft_letters(s, c);
	}
	res[word] = NULL;
	return (res);
}
