/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:51:03 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/26 00:06:08 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		valid_map(char **map)
// {
// 	int	i;
// 	int	j;

// 	while (map[i])
// }

int		valid_path(t_map *map_data)
{
	if (!(ft_strncmp(map_data->east, map_data->west, ft_strlen(map_data->east))
	|| ft_strncmp(map_data->east, map_data->west, ft_strlen(map_data->west))
	|| ft_strncmp(map_data->east, map_data->north, ft_strlen(map_data->east))
	|| ft_strncmp(map_data->east, map_data->north, ft_strlen(map_data->north))
	|| ft_strncmp(map_data->east, map_data->south, ft_strlen(map_data->east))
	|| ft_strncmp(map_data->east, map_data->south, ft_strlen(map_data->south))
	|| ft_strncmp(map_data->west, map_data->north, ft_strlen(map_data->west))
	|| ft_strncmp(map_data->west, map_data->north, ft_strlen(map_data->north))
	|| ft_strncmp(map_data->west, map_data->south, ft_strlen(map_data->west))
	|| ft_strncmp(map_data->west, map_data->south, ft_strlen(map_data->south))
	|| ft_strncmp(map_data->north, map_data->south, ft_strlen(map_data->north))
	|| ft_strncmp(map_data->north, map_data->south, ft_strlen(map_data->south))
	))
		return (0);
	return (1);
}