/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:43:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 22:14:16 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	height_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

float		vertic_length(t_ray *ray, t_all *all)
{
	float	vertical;
	int		x_offset;

	x_offset = SCALE;
	ray->x = all->player->x;
	ray->y = all->player->y;
	if ((ray->an < (M_PI_2)) || (ray->an > (3 * M_PI_2)))
		ray->x = (int)(all->player->x / SCALE) * SCALE + SCALE;
	if ((ray->an > (M_PI_2)) && (ray->an < (3 * M_PI_2)))
	{
		ray->x = (int)(all->player->x / SCALE) * SCALE - 0.001;
		x_offset *= -1;
	}
	ray->y = all->player->y + (ray->x - all->player->x) * tan(ray->an);
	while (ray->x >= 0 && ray->y >= 0 && ray->x < ft_strlen(all->map_data->map
	[(int)all->player->y / SCALE]) * SCALE && ray->y <
	height_len(all->map_data->map) * SCALE && all->map_data->map[(int)(ray->y /
	SCALE)][(int)(ray->x / SCALE)] != '1')
	{
		ray->x += x_offset;
		ray->y += x_offset * tan(ray->an);
	}
	vertical = sqrtf(pow(all->player->x - ray->x, 2) +
	pow(all->player->y - ray->y, 2));
	return (vertical);
}

float		horizont_length(t_ray *ray, t_all *all)
{
	float	horizontal;
	int		y_offset;

	y_offset = SCALE;
	ray->x = all->player->x;
	ray->y = all->player->y;
	if (ray->an < M_PI)
		ray->y = (int)(all->player->y / SCALE) * SCALE + SCALE;
	else if (ray->an > M_PI)
	{
		ray->y = (int)(all->player->y / SCALE) * SCALE - 0.001;
		y_offset *= -1;
	}
	ray->x = all->player->x + (ray->y - all->player->y) / tan(ray->an);
	while (ray->x >= 0 && ray->y >= 0 && ray->x < ft_strlen(all->map_data->map
	[(int)(all->player->y / SCALE)]) * SCALE && (ray->y) <
	height_len(all->map_data->map) * SCALE &&
	all->map_data->map[(int)(ray->y / SCALE)][(int)(ray->x / SCALE)] != '1')
	{
		ray->y += y_offset;
		ray->x += y_offset / tan(ray->an);
	}
	horizontal = sqrtf(pow(all->player->x - ray->x, 2) +
	pow(all->player->y - ray->y, 2));
	return (horizontal);
}

void		printing(t_all *all, t_ray *ray, int num_ray)
{
	float	x;

	x = (all->text_we->width * (SCALE - (int)ray[1].y % SCALE)) / SCALE - 0.1;
	if (ray[0].len < ray[1].len && (ray[0].an >= M_PI && ray[0].an < 2 * M_PI))
	{
		x = (all->text_no->width * ((int)ray[0].x % SCALE)) / SCALE;
		all->dist = ray[0].len * cos(fix_ray(all->player->dir - ray[0].an));
		print_3d(all, num_ray, x, all->text_no);
	}
	else if (ray[0].len < ray[1].len && (ray[1].an >= 0 && ray[0].an < M_PI))
	{
		x = (all->text_so->width * (SCALE -
			(int)ray[0].x % SCALE)) / SCALE - 0.1;
		all->dist = ray[0].len * cos(fix_ray(all->player->dir - ray[0].an));
		print_3d(all, num_ray, x, all->text_so);
	}
	else if (ray[1].len < ray[0].len && (ray[1].an > 3 * M_PI_2
		|| ray[1].an < M_PI / 2))
	{
		x = (all->text_ea->width * ((int)ray[1].y % SCALE)) / SCALE;
		all->dist = ray[1].len * cos(fix_ray(all->player->dir - ray[1].an));
		print_3d(all, num_ray, x, all->text_ea);
	}
	else
		print_3d(all, num_ray, x, all->text_we);
}

void		cast_rays(t_all *all)
{
	t_ray		ray[2];
	int			num_ray;

	ray[0].an = all->player->dir - M_PI / 6;
	ray[1].an = all->player->dir - M_PI / 6;
	num_ray = 0;
	malloc_arr(all);
	while (num_ray < all->map_data->screen_width)
	{
		ray[0].len = horizont_length(&ray[0], all);
		ray[1].len = vertic_length(&ray[1], all);
		all->dist = ray[1].len * cos(fix_ray(all->player->dir - ray[1].an));
		printing(all, ray, num_ray);
		ray[0].an = fix_ray(ray[0].an + (M_PI / 3)
			/ all->map_data->screen_width);
		ray[1].an = fix_ray(ray[1].an + (M_PI / 3)
			/ all->map_data->screen_width);
		num_ray++;
	}
	print_sprites(all);
}
