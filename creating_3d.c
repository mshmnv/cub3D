/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/06 17:37:51 by lbagg            ###   ########.fr       */
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

void	print_3d(t_all *all, float dist, int num_ray)
{
	int	line_height;
	int	line_offset;
	int	end;

	line_height = (SCALE * SCREEN_HEIGHT) / dist;
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	line_offset = SCREEN_HEIGHT / 2 - line_height / 2;
	end = line_offset + line_height;
	while (line_offset <= end)
	{
		pixel_put(all->params, num_ray + 1, line_offset, 0xDAC890);
		line_offset++;
	}
}