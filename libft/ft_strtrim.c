/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:29:10 by lbagg             #+#    #+#             */
/*   Updated: 2020/05/16 12:32:42 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == 0)
			break ;
		start++;
	}
	end = ft_strlen(s1);
	while (s1[end - 1])
	{
		if (ft_strchr(set, s1[end - 1]) == 0)
			break ;
		end--;
	}
	if (start >= end)
		return (ft_strdup(""));
	res = ft_calloc(end - start + 1, sizeof(char));
	ft_strlcpy(res, s1 + start, end - start + 1);
	return (res);
}
