/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 13:52:04 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			pixel_put(all->data, x, y, all->map_data->ceiling_color);
			y++;
		}
		if (y >= all->map_data->screen_height / 2)
			while (y < all->map_data->screen_height)
			{
				pixel_put(all->data, x, y, all->map_data->floor_color);
				y++;
			}
		x++;
	}
}

float	fix_ray(float ray)
{
	if (ray > 2 * M_PI)
		ray -= 2 * M_PI;
	else if (ray < 0)
		ray += 2 * M_PI;
	return (ray);
}

void	print_3d(t_all *all, int n_ray, int x, t_texture *texture)
{
	int		line_height;
	int		line_start;
	int		line_end;
	float	y_step;
	float	y;

	line_height = (SCALE * all->map_data->screen_height) / all->dist;
	y_step = (float)texture->height / (float)line_height;
	line_start = all->map_data->screen_height / 2 - line_height / 2;
	if (line_start < 0)
		line_start = 0;
	line_end = line_start + line_height;
	if (line_end > all->map_data->screen_height)
		line_end = all->map_data->screen_height;
	y = (line_start - all->map_data->screen_height / 2
	+ line_height / 2) * y_step;
	while (line_start < line_end)
	{
		pixel_put(all->data, n_ray, line_start, *(unsigned int *)(texture->addr
		+ (((int)y * texture->line_len) + (x * (texture->bpp / 8)))));
		line_start++;
		y += y_step;
	}
}
