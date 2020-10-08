/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/08 19:09:17 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(t_all *all, int length, float dir)
{
	float	x;
	float	y;
	int	i;

	x = all->player->x;
	y = all->player->y;
	i = 0;
	while (i < length)
	{
		pixel_put(all->params, x + i * cos(dir), y + i * sin(dir), 0x5FA975);
		i++;
	}
}

int		height_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

float		vertic_length(t_player *ray, t_all *all)
{
	float	vertical;
	int		x_offset;

	x_offset = SCALE;
	if ((ray->dir < (PI / 2)) || (ray->dir > (3 * PI / 2)))
		ray->x = (int)(all->player->x / SCALE) * SCALE + SCALE;
	if ((ray->dir > (PI / 2)) && (ray->dir < (3 * PI / 2)))
	{
		ray->x = (int)(all->player->x / SCALE) * SCALE - 0.001;
		x_offset *= -1;
	}
	ray->y = all->player->y + (ray->x - all->player->x) * tan(ray->dir);
	while (ray->x >= 0 && ray->y >= 0 && ray->x < ft_strlen(all->map[(int)all->player->y / SCALE]) * SCALE &&
	ray->y < height_len(all->map) * SCALE && all->map[(int)(ray->y / SCALE)][(int)(ray->x / SCALE)] != '1')
	{
		ray->x += x_offset;
		ray->y += x_offset * tan(ray->dir);
	}
	vertical = sqrtf(pow(all->player->x - ray->x, 2) + pow(all->player->y - ray->y, 2));
	return (vertical);
}

float		horizont_length(t_player *ray, t_all *all)
{
	float	horizontal;
	int		y_offset;

	y_offset = SCALE;
	if (ray->dir < PI)
		ray->y = (int)(all->player->y / SCALE) * SCALE + SCALE;
	else if (ray->dir > PI)
	{
		ray->y = (int)(all->player->y / SCALE) * SCALE - 0.001;
		y_offset *= -1;
	}
	ray->x = all->player->x + (ray->y - all->player->y) / tan(ray->dir);
	while (ray->x >= 0 && ray->y >= 0  && ray->x < ft_strlen(all->map[(int)(all->player->y / SCALE)]) * SCALE &&
	(ray->y) < height_len(all->map) * SCALE && all->map[(int)(ray->y / SCALE)][(int)(ray->x / SCALE)] != '1')
	{
		ray->y += y_offset;
		ray->x += y_offset / tan(ray->dir);
	}
	horizontal = sqrtf(pow(all->player->x - ray->x, 2) + pow(all->player->y - ray->y, 2));
	return (horizontal);
}

void	cast_rays(t_all *all)
{
	t_player	ray_h;
	t_player	ray_v;
	float		start;
	float		end;
	float		horizontal;
	float		vertical;
	int			num_ray;
	float		ang_dist;

	end = all->player->dir + PI / 6;
	start = all->player->dir - PI / 6;
	ray_h = *all->player;
	ray_v = *all->player;
	num_ray = 0;
	while (num_ray < SCREEN_WIDTH)
	{
		start = fix_ray(start);
		ray_h.dir = start;
		ray_v.dir = start;
		horizontal = horizont_length(&ray_h, all);
		vertical = vertic_length(&ray_v, all);
		if (horizontal < vertical && horizontal > 0)
		{
			print_line(all, horizontal, ray_h.dir);
			ang_dist = all->player->dir - ray_h.dir;
			ang_dist = fix_ray(ang_dist);
			horizontal = horizontal * cos(ang_dist);
			print_3d(all, horizontal, num_ray, &ray_h);
		}
		else if (vertical < horizontal && vertical > 0)
		{
			print_line(all, vertical, ray_v.dir);
			ang_dist = all->player->dir - ray_v.dir;
			ang_dist = fix_ray(ang_dist);
			vertical = vertical * cos(ang_dist);
			print_3d(all, vertical, num_ray, &ray_v);
		}
		start += (PI / 3 ) / SCREEN_WIDTH;
		num_ray++;
	}
}