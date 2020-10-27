/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:17:53 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 17:40:41 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(int key)
{
	if (key == ER_OPEN)
		ft_putendl_fd("Error opening file", 1);
	if (key == ER_ARG)
		ft_putendl_fd("Invalid arguments", 1);
	if (key == ER_MALLOC)
		ft_putendl_fd("Malloc error", 1);
	if (key == ER_TEXT_PATH)
		ft_putendl_fd("Invalid texture path", 1);
	if (key == ER_RES_SIZE)
		ft_putendl_fd("Invalid resolution size", 1);
	if (key == ER_MORE_PLAYER)
		ft_putendl_fd("More then one player on the map", 1);
	if (key == ER_SCREENSHOT)
		ft_putendl_fd("Failed to create screenshot", 1);
	if (key == ER_MAP)
		ft_putendl_fd("Invalid map", 1);
	if (key == ER_COLOR)
		ft_putendl_fd("Invalid floor and ceiling color", 1);
	exit(0);
}
