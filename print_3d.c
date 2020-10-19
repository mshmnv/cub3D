/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/19 19:10:24 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites(t_all *all)
{
	float	x;
	float	y;
	
	float	sprite_dir;
	float	sprite_dist;

	float	height;
	float	y_step;
	float	y_start;
	float	y_end;
	float	x_start;
	float	x_mid;
	float	x_end;


	y = 0;
	while (all->map[(int)y])
	{
		x = 0;
		while (all->map[(int)y][(int)x])
		{
			if (all->map[(int)y][(int)x] == '2')
			{
				sprite_dir = atan2(y * SCALE - all->player->y, x * SCALE - all->player->x) + PI / 6;
				sprite_dir = fix_ray(sprite_dir);
				// printf("%f\n", sprite_dir - all->player->dir);
				if ((sprite_dir - all->player->dir) > 0 && (sprite_dir - all->player->dir) < PI / 3)
				{
					pixel_put(all->params, x * 16, y * 16, 0xffffff);
					sprite_dist = sqrt(pow(all->player->x - x * SCALE - SCALE / 2, 2) + pow(all->player->y - y * SCALE - SCALE / 2, 2));
					x_mid = all->sprite->width / (PI / 6) * sprite_dir - all->player->dir;
					print_3d(all, sprite_dist, x * SCALE - SCALE, all->sprite->height / 2, all->sprite);
				}
			}
			x++;
		}
		y++;
	}
}

void	color_screen(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	while (x < all->map_data->screen_width)
	{
		y = 0;
		while (y < all->map_data->screen_height / 2)
		{
			pixel_put(all->params, x, y, all->map_data->ceiling_color);
			y++;
		}
		if (y >= all->map_data->screen_height / 2)
			while (y < all->map_data->screen_height)
			{
				pixel_put(all->params, x, y, all->map_data->floor_color);
				y++;
			}
		x++;
	}
}

float	fix_ray(float ray)
{
	if (ray > 2 * PI)
		ray -= 2 * PI;
	else if (ray < 0)
		ray += 2 * PI;
	return (ray);
}

void	print_3d(t_all *all, float dist, int num_ray, int text_x, t_texture *texture)
{
	char    *color;
	int		line_height;
	int		line_start;
	int		line_end;
	float	y_step;
	float	text_y;
	int		y_print;


	line_height = (SCALE * all->map_data->screen_height) / dist;
	y_step = (float)texture->height / (float)line_height;
	line_start = all->map_data->screen_height / 2 - line_height / 2;
	if (line_start < 0)
		line_start = 0;
	line_end = line_start + line_height;
	if (line_end > all->map_data->screen_height)
		line_end = all->map_data->screen_height;
	text_y = (line_start - all->map_data->screen_height / 2 + line_height / 2) * y_step;
	while (line_start < line_end)
	{
		color = texture->addr + (((int)text_y * texture->line_length) + (text_x * (texture->bits_per_pixel / 8)));
		pixel_put(all->params, num_ray, line_start, *(unsigned int *)color);
		line_start++;
		text_y += y_step;
	}
}
