/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:05:52 by lbagg             #+#    #+#             */
/*   Updated: 2020/05/03 19:52:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (n-- > 0)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
