/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:17:53 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/20 13:41:38 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char key)
{
	if (key == 'a')
		ft_putendl_fd("Invalid number of arguments", 1);
	if (key == 'm')
		ft_putendl_fd("Malloc error", 1);
	if (key == 't')
		ft_putendl_fd("Invalid texture path", 1);
	if (key == 'r')
		ft_putendl_fd("Invalid resolution size", 1);
	if (key == 'p')
		ft_putendl_fd("More then one player on the map", 1);
	exit(0);
}