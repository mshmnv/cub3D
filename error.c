/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:17:53 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/25 10:58:42 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_all *all)
{

}

void	error(int key)
{
	if (key == er_open)
		ft_putendl_fd("Error opening file", 1);
	if (key == er_arg)
		ft_putendl_fd("Invalid arguments", 1);
	if (key == er_malloc)
		ft_putendl_fd("Malloc error", 1);
	if (key == er_text_path)
		ft_putendl_fd("Invalid texture path", 1);  // + все текстуры разные
	if (key == er_res_size)
		ft_putendl_fd("Invalid resolution size", 1);	// + не больше экрана устройства
	if (key == er_more_players)
		ft_putendl_fd("More then one player on the map", 1);
	if (key == er_screenshot)
		ft_putendl_fd("Failed to create screenshot", 1);
	if (key == er_map)
		ft_putendl_fd("Invalid map", 1);
	if (key == er_color)
		ft_putendl_fd("Invalid floor and ceiling color", 1);
	// только один флаг и все есть RCF NWES
	exit(0);
}