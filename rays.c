/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/20 12:57:33 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(t_all *all, int length, float dir)
{
	float	x;
	float	y;
	int		i;

	x = all->player->x * 16 / SCALE;
	y = all->player->y * 16 / SCALE;
	i = 0;
	while (i <= (length * 16 / SCALE))
	{
		pixel_put(all->params, x + i * cos(dir), y + i * sin(dir), 0xE45F42);
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
	t_player	ray[2];
	float		start;
	float		end;
	float		horizontal;
	float		vertical;
	float		dist;
	int			num_ray;
	float		text_x;
	t_texture	*texture;

	end = all->player->dir + PI / 6;
	start = all->player->dir - PI / 6;
	ray[0] = *all->player;
	ray[1] = *all->player;
	num_ray = 0;
	while (num_ray < all->map_data->screen_width)
	{
		start = fix_ray(start);
		ray[0].dir = start;
		ray[1].dir = start;
		horizontal = horizont_length(&ray[0], all);
		vertical = vertic_length(&ray[1], all);
		text_x = (all->texture_we->width * (SCALE - (int)ray[1].y % SCALE)) / SCALE - 0.1;
		dist = vertical * cos(fix_ray(all->player->dir - ray[1].dir));
		texture = all->texture_we;
		if (horizontal < vertical && (ray[0].dir >= PI && ray[0].dir < 2 * PI))
		{
			text_x = (all->texture_no->width * ((int)ray[0].x % SCALE)) / SCALE;
			print_line(all, horizontal, ray[0].dir);
			dist = horizontal * cos(fix_ray(all->player->dir - ray[0].dir));
			texture = all->texture_no;
		}
		else if (horizontal < vertical && (ray[1].dir >= 0 && ray[0].dir < PI))
		{
			text_x = (all->texture_so->width * (SCALE - (int)ray[0].x % SCALE)) / SCALE - 0.1;
			print_line(all, horizontal, ray[0].dir);
			dist = horizontal * cos(fix_ray(all->player->dir - ray[0].dir));
			texture = all->texture_so;
		}
		else if (vertical < horizontal && (ray[1].dir > 3 * PI / 2 || ray[1].dir < PI / 2))
		{
			text_x = (all->texture_ea->width * ((int)ray[1].y % SCALE)) / SCALE;
			print_line(all, vertical, ray[1].dir);
			dist = vertical * cos(fix_ray(all->player->dir - ray[1].dir));
			texture = all->texture_ea;
		}
		else
			print_line(all, vertical, ray[1].dir);
		print_3d(all, dist, num_ray, text_x, texture);
		start += (PI / 3 ) / all->map_data->screen_width;
		num_ray++;
	}
}