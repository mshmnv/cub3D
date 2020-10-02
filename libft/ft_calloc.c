/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 08:47:40 by lbagg             #+#    #+#             */
/*   Updated: 2020/05/03 19:51:57 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmend, size_t size)
{
	void *ptr;

	ptr = malloc(nmend * size);
	if (ptr)
		ft_bzero(ptr, nmend * size);
	return (ptr);
}
