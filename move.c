/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:37:54 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/28 16:10:49 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		up(t_all *all)
{
	int		x;
	int		y;

	x = all->player->x + cos(all->player->dir) * 4;
	y = all->player->y + sin(all->player->dir) * 4;
	if (all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '1'
	&& all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '2')
		all->player->x = x;
	if (all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '1'
	&& all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '2')
		all->player->y = y;
}

void		down(t_all *all)
{
	int		x;
	int		y;

	x = all->player->x - cos(all->player->dir) * 4;
	y = all->player->y - sin(all->player->dir) * 4;
	if (all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '1'
	&& all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '2')
		all->player->x = x;
	if (all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '1'
	&& all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '2')
		all->player->y = y;
}

void		right(t_all *all)
{
	int		x;
	int		y;

	x = all->player->x + sin(all->player->dir) * 4;
	y = all->player->y - cos(all->player->dir) * 4;
	if (all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '1'
	&& all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '2')
		all->player->x = x;
	if (all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '1'
	&& all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '2')
		all->player->y = y;
}

void		left(t_all *all)
{
	int		x;
	int		y;

	x = all->player->x - sin(all->player->dir) * 4;
	y = all->player->y + cos(all->player->dir) * 4;
	if (all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '1'
	&& all->map_data->map[(int)all->player->y / SCALE][x / SCALE] != '2')
		all->player->x = x;
	if (all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '1'
	&& all->map_data->map[y / SCALE][(int)all->player->x / SCALE] != '2')
		all->player->y = y;
}
