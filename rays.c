/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/02 20:00:26 by lbagg            ###   ########.fr       */
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
	// while (i < length)
	// {
	// 	x += cos(player->dir);
	// 	y += sin(player->dir);
	// 	pixel_put(all->params, x, y, 0xDAC890);
	// 	i++;
	// }
}

int		height_len(char **map, int ray_x, int ray_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[j])
		{
			j++;
		}
		i++;
	}
	return (i);
}

int		vertic_length(t_player *ray, t_all *all)
{
	int	vertical;
	int	x_offset;

	*ray = *all->player;
	if ((all->player->dir < (PI / 2)) || (all->player->dir > (3 * PI / 2)))		// right
	{
		ray->x = (all->player->x / 16) * 16 + 16;
		x_offset = 16;
	}
	if ((all->player->dir > (PI / 2)) && (all->player->dir < (3 * PI / 2)))		// left
	{
		ray->x = (all->player->x / 16) * 16 - 1;
		x_offset = -16;
	}
	ray->y = all->player->y + (ray->x - all->player->x) * tan(all->player->dir);
	while ((ray->x > 0) && (ray->y > 0) && ((ray->y / 16) < height_len(all->map, ray->y, ray->x)) && (all->map[(int)ray->y / 16][(int)ray->x / 16] != '1'))
	{
		pixel_put(all->params, ray->x, ray->y, 0xDAC890);
		ray->x += x_offset;
		ray->y += x_offset * tan(all->player->dir);
	}
	// printf("%f %f %f\n", all->player->x, all->player->y, all->player->dir);
	// printf("%f %f\n", ray->x, ray->y);
	vertical = sqrt(pow(all->player->x - ray->x, 2) + pow(all->player->y - ray->y, 2));
	// printf("%d\n", vertical);
	return (vertical);
}

int		horizont_length(t_player *ray, t_all *all)
{
	int	horizontal;
	int	y_offset;

	*ray = *all->player;
	if (all->player->dir < PI)
	{
		ray->y = (all->player->y / 16) * 16 + 16;
		y_offset = 16;
	}
	else if (all->player->dir > PI)
	{
		ray->y = (all->player->y / 16) * 16 - 1;
		y_offset = -16;
	}
	while ((ray->x > 0) && (ray->y > 0)  && ((ray->x / 16) < ft_strlen(all->map[(int)all->player->y / 16])) && (all->map[(int)ray->y / 16][(int)ray->x / 16] != '1'))
	{
		ray->y += y_offset;
		ray->x += y_offset / tan(all->player->dir);
	}
	horizontal = sqrt(pow(all->player->x - ray->x, 2) + pow(all->player->y - ray->y, 2));
	return (horizontal);
}

void	cast_ray(t_all *all)
{
	t_player	ray;
	int			horizontal;
	int			vertical;


	horizontal = horizont_length(&ray, all);
	print_line(all, &ray, all->player, horizontal);

	// vertical = vertic_length(&ray, all);
	// printf("%f %f %f\n", all->player->x, all->player->y, all->player->dir);
	// printf("%f %f\n", ray.x, ray.y);
	// printf("%d\n", vertical);
	// print_line(all, &ray, all->player, vertical);
}
