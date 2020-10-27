/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:22:35 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 22:23:17 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_all *all, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				all->player->x = x * SCALE + SCALE / 2;
				all->player->y = y * SCALE + SCALE / 2;
				(map[y][x] == 'E') ? all->player->dir = 0 : 0;
				(map[y][x] == 'N') ? all->player->dir = 3 * M_PI_2 : 0;
				(map[y][x] == 'W') ? all->player->dir = M_PI : 0;
				(map[y][x] == 'S') ? all->player->dir = M_PI_2 : 0;
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
