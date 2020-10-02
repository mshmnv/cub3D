/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/09/22 14:10:14 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(t_all *all, t_player *ray, t_player *player, int length)
{
	int	x;
	int	y;
	int	i;

	x = player->x;
	y = player->y;
	
	pixel_put(all->params, ray->x, ray->y, 0xDAC890);
	i = 0;
	while (i < length)
	{
		x += cos(player->dir);
		y += sin(player->dir);
		pixel_put(all->params, x, y, 0xDAC890);
		i++;
	}
}

void	cast_ray(t_all *all)
{
	t_player	ray;
	int			horizontal;
	int			vertical;
	int			y_offset;

	ray = *all->player;
	if (all->player->dir < PI)
	{
		ray.y = (all->player->y / 16) * 16 + 16;
		y_offset = 16;
	}
	else if (all->player->dir > PI)
	{
		ray.y = (all->player->y / 16) * 16 - 1;
		y_offset = -16;
	}
	ray.x = all->player->x + (ray.y - all->player->y ) / tan(all->player->dir);
	
	// printf("%d - %d\n", all->player->x, all->player->y);
	// printf("%d - %d\n\n", ray.x, ray.y);

	while (all->map[ray.y / 16][ray.x / 16] != '1')
	{
		ray.y += y_offset;
		ray.x += y_offset / tan(all->player->dir);
	}
	horizontal = sqrt(pow(all->player->x - ray.x, 2) + pow(all->player->y - ray.y, 2));
	// printf("%d\n", horizontal);
	print_line(all, &ray, all->player, horizontal);
}
