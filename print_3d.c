/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/08 20:10:50 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_screen(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			pixel_put(all->params, x, y, 0xE45F42);
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

void	print_3d(t_all *all, float dist, int num_ray, t_player *ray)
{
	int		color;
	int		line_height;
	int		line_offset;
	int		line_end;
	float	y_step;
	int		text_x;
	float	text_y;

	text_y = 0;
	text_x = 0;
	text_x = ((float)all->texture->width / (float)SCREEN_WIDTH) * num_ray;    //нет - считать с помощью луча
	y_step = (float)all->texture->height / (float)SCREEN_HEIGHT;
	line_height = (SCALE * SCREEN_HEIGHT) / dist;
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	line_offset = SCREEN_HEIGHT / 2 - line_height / 2;
	line_end = line_offset + line_height;
	while (line_offset < line_end)
	{
		color = *(all->texture->addr + (((int)text_y * all->texture->line_length) + (text_x * (all->texture->bits_per_pixel / 8))));
		pixel_put(all->params, num_ray, line_offset, color);
		line_offset++;
		text_y += y_step;
	}
}