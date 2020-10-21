/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/21 20:33:41 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites(t_all *all)
{
	char	*color;
	float	x;
	float	y;
	float	sprite_dir;
	float	sprite_dist;
	int		x_mid;
	int		x_start;
	int 	x_end;
	int		sprite_height;
	int		y_end;
	int 	y_start;
	int		pp;
	int		screen_pos;
	int 	y_save;

	float		y_text;
	int			x_text;
	float		y_step;
	float		save_y_text;
	
	y = 0;
	while (all->map[(int)y])
	{
		x = 0;
		while (all->map[(int)y][(int)x])
		{
			if (all->map[(int)y][(int)x] == '2')
			{
				sprite_dir = atan2(y * SCALE + SCALE / 2 - all->player->y, x * SCALE + SCALE / 2 - all->player->x);
				sprite_dir = fix_ray(sprite_dir);
				if ((sprite_dir - all->player->dir) >= - PI / 6 && (sprite_dir - all->player->dir) <= PI / 6)
				{
					pixel_put(all->params, x * 16, y * 16, 0xFFFFFF);
					sprite_dist = sqrt(pow(all->player->x - x * SCALE + SCALE / 2, 2) + pow(all->player->y - y * SCALE + SCALE / 2, 2));
					pp = all->map_data->screen_width / 2 / tan(PI / 6);
					screen_pos = all->map_data->screen_width / 2 + pp * tan(sprite_dir - all->player->dir);
					sprite_height = fabs((SCALE * pp) / (sprite_dist * cos(sprite_dir - all->player->dir)));

					x_start = screen_pos - sprite_height / 2;
					x_end = screen_pos + sprite_height / 2;
					if (x_start < 0)
						break ;
					if (x_end > all->map_data->screen_width)
						x_end = all->map_data->screen_width;
					
					y_start = all->map_data->screen_height / 2 - sprite_height / 2;
					y_end = all->map_data->screen_height / 2 + sprite_height / 2;
					if (y_start < 0)
						y_start = 0;
					if (y_end > all->map_data->screen_height)
						y_end = all->map_data->screen_height;
					y_save = y_start;

						
					y_step = (float)all->sprite->height / (float)sprite_height;
					y_text = (y_start - all->map_data->screen_height / 2  + sprite_height / 2) * y_step;
					save_y_text  = y_text;
					while (x_start < x_end)
					{
						y_start = y_save;
						y_text = save_y_text;
						while (y_start < y_end)
						{
							x_text = (all->sprite->width * (x_start % SCALE)) / SCALE;
							color = all->sprite->addr + (((int)y_text * all->sprite->line_length) + (x_text * (all->sprite->bits_per_pixel / 8)));
							if (color != 0x000000)
								pixel_put(all->params, x_start, y_start, *(unsigned int *)color);
							y_start++;
							y_text += y_step;
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
