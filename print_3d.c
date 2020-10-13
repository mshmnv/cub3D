/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/13 18:28:29 by lbagg            ###   ########.fr       */
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
			pixel_put(all->params, x, y, 0xDAC890);
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

void	print_3d(t_all *all, float dist, int num_ray, int text_x)
{
	char    *color;
	int		line_height;
	int		line_start;
	int		line_end;
	float	y_step;
	float	text_y;
	int y_print;


	line_height = (SCALE * SCREEN_HEIGHT) / (float)dist;
	y_step = (float)all->texture->height / (float)line_height;
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	line_start = SCREEN_HEIGHT / 2 - line_height / 2;
	line_end = line_start + line_height;
	int save = line_start;
	text_y = (line_start - (float)SCREEN_HEIGHT / 2 + (float)line_height / 2) * y_step;
	while (line_start < line_end)
	{
		color = all->texture->addr + (((int)text_y * all->texture->line_length) + (text_x * (all->texture->bits_per_pixel / 8)));
		pixel_put(all->params, num_ray, line_start, *(unsigned int *)color);
		line_start++;
		text_y += y_step;
	}
}

/* void	print_3d(t_all *all, float dist, int num_ray, int text_x)
{
	char    *color;
	int		line_height;
	int		line_start;
	int		line_end;
	float	y_step;
	float	text_y;

	float pp = SCREEN_WIDTH / 2 / tan(PI / 6);

	line_height = (SCALE * pp) / dist;
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	line_start = SCREEN_HEIGHT / 2 - line_height / 2;
	line_end = line_start + line_height;
	y_step = (float)all->texture->height / (float)line_height;
	while (line_start < line_end)
	{
		text_y = ((float)line_start - ((float)SCREEN_HEIGHT / 2 - (float)line_height / 2)) / (float)line_height;
		text_y *= (float)all->texture->height;
		color = (all->texture->addr + (((int)text_y * all->texture->line_length) + (text_x * (all->texture->bits_per_pixel / 8))));
		pixel_put(all->params, num_ray, line_start, *(unsigned int *)color);
		line_start++;
	}
} */