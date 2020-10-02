/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:36:31 by lbagg             #+#    #+#             */
/*   Updated: 2020/05/19 09:38:04 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (strlen - 1 < start)
		return (ft_strdup(""));
	strlen = ft_strlen(&s[start]);
	if (strlen < len)
		strlen++;
	else
		strlen = len + 1;
	sub = ft_calloc(strlen, sizeof(char));
	if (sub)
		ft_strlcpy(sub, &s[start], strlen);
	return (sub);
}
