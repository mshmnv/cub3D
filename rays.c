/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/19 17:29:33 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(t_all *all, int length, float dir)
{
	float	x;
	float	y;
	int	i;

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
	t_player	ray_h;
	t_player	ray_v;
	float		start;
	float		end;
	float		horizontal;
	float		vertical;
	float		dist;
	int			num_ray;
	float		ang_dist;
	float		text_x;
	t_texture	*texture;
	

	end = all->player->dir + PI / 6;
	start = all->player->dir - PI / 6;
	ray_h = *all->player;
	ray_v = *all->player;
	num_ray = 0;
	while (num_ray < all->map_data->screen_width)
	{
		start = fix_ray(start);
		ray_h.dir = start;
		ray_v.dir = start;
		horizontal = horizont_length(&ray_h, all);
		vertical = vertic_length(&ray_v, all);
		text_x = (all->texture_we->width * (SCALE - (int)ray_v.y % SCALE)) / SCALE - 0.1;
		ang_dist = all->player->dir - ray_v.dir;
		dist = vertical;
		texture = all->texture_we;
		if (horizontal < vertical && (ray_h.dir >= PI && ray_h.dir < 2 * PI))
		{
			text_x = (all->texture_no->width * ((int)ray_h.x % SCALE)) / SCALE;
			print_line(all, horizontal, ray_h.dir);
			ang_dist = all->player->dir - ray_h.dir;
			dist = horizontal;
			texture = all->texture_no;
		}
		else if (horizontal < vertical && (ray_h.dir >= 0 && ray_h.dir < PI))
		{
			text_x = (all->texture_so->width * (SCALE - (int)ray_h.x % SCALE)) / SCALE - 0.1;
			print_line(all, horizontal, ray_h.dir);
			ang_dist = all->player->dir - ray_h.dir;
			dist = horizontal;
			texture = all->texture_so;
		}
		else if (vertical < horizontal && (ray_v.dir > 3 * PI / 2 || ray_v.dir < PI / 2))
		{
			text_x =  (all->texture_ea->width * ((int)ray_v.y % SCALE)) / SCALE;
			print_line(all, vertical, ray_v.dir);
			ang_dist = all->player->dir - ray_v.dir;
			dist = vertical;
			texture = all->texture_ea;
		}
		else
			print_line(all, vertical, ray_v.dir);
		ang_dist = fix_ray(ang_dist);
		dist = dist * cos(ang_dist);
		print_3d(all, dist, num_ray, text_x, texture);
		start += (PI / 3 ) / all->map_data->screen_width;
		num_ray++;
	}
}