/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/21 14:16:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites(t_all *all)
{
	float	x;
	float	y;
	float	sprite_dir;
	float	sprite_dist;

	int		x_mid;
	int		x_start;
	int 	x_end;
	int		line_height;
	int		line_end;
	int 	line_start;
	int		pp;
	int		screen_pos;
	
	y = 0;
	while (all->map[(int)y])
	{
		x = 0;
		while (all->map[(int)y][(int)x])
		{
			if (all->map[(int)y][(int)x] == '2')
			{
				sprite_dir = atan2(y * SCALE + SCALE / 2 - all->player->y, x * SCALE + SCALE / 2 - all->player->x) + PI / 6;
				sprite_dir = fix_ray(sprite_dir);
				if ((sprite_dir - all->player->dir) >= 0 && (sprite_dir - all->player->dir) <= PI / 3)
				{
					pixel_put(all->params, x * 16, y * 16, 0xFFFFFF);
					sprite_dist = sqrt(pow(all->player->x - x * SCALE + SCALE / 2, 2) + pow(all->player->y - y * SCALE + SCALE / 2, 2));
					// x_mid = all->map_data->screen_width * sprite_dir / (PI / 3);
					// PP -  расстояние до горизонта
					pp = all->map_data->screen_width / 2 / tan(PI / 6);
					screen_pos = all->map_data->screen_width / 2 + pp / tan(sprite_dir);
					x_start = screen_pos - all->sprite->width / 2;
					x_end = (x * SCALE + SCALE / 2) + all->sprite->width / 2;
					printf("%d  - %d\n", x_start, x_end);
					// if (x_start < 0)
					// 	x_start = 0;
					// if (x_end > all->map_data->screen_height)
					// 	x_end = all->map_data->screen_height;
					line_height = (SCALE * all->map_data->screen_height) / sprite_dist;
					line_start = all->map_data->screen_height / 2 - line_height / 2;
					if (line_start < 0)
						line_start = 0;
					line_end = line_start + line_height;
					if (line_end > all->map_data->screen_height)
						line_end = all->map_data->screen_height;
					while(x_start < x_end)
					{
						while (line_start < line_end)
						{
							// color = texture->addr + (((int)text_y * texture->line_length) + (text_x * (texture->bits_per_pixel / 8)));
							pixel_put(all->params, x_start, line_start, 0xFFFFFF);
							line_start++;
						}
						x_start++;
					}
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
