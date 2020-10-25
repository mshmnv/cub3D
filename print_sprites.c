/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 10:05:26 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/25 10:31:03 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites(t_all *all)
{
	t_sprite	*tmp;

	tmp = all->sprites;
	while (tmp)
	{
		tmp->dist = sqrt(pow(all->player->x - tmp->x, 2) +
				pow(all->player->y - tmp->y, 2));
		tmp->dir = fix_ray(atan2(tmp->y - all->player->y,
				tmp->x - all->player->x));
		tmp = tmp->next;
	}
	tmp = all->sprites;
	while (tmp != NULL)
	{
		if (no_walls(all, tmp))
			culc_sprite(all, tmp);
		tmp = tmp->next;
	}
}

int		no_walls(t_all *all, t_sprite *tmp)
{
	float	x;
	float	y;
	int		i;

	x = all->player->x;
	y = all->player->y;
	i = 0;
	while (i <= tmp->dist)
	{
		if (all->map[(int)(y + i * sin(tmp->dir)) / SCALE]
			[(int)(x + i * cos(tmp->dir)) / SCALE] == '1')
			return (0);
		i++;
	}
	return (1);
}

void	culc_sprite(t_all *all, t_sprite *sprite)
{
	int		proj_plane;
	float	coef;
	t_point	point;

	sprite->dir = sprite->dir - all->player->dir;
	if (sprite->dir > -PI / 6 && sprite->dir < PI / 6)
	{
		pixel_put(all->params, sprite->x / SCALE * 16, sprite->y / SCALE * 16,
				0xFFFFFF);
		proj_plane = all->map_data->screen_width / (2 * tan(PI / 6));
		sprite->height = fabs((SCALE * proj_plane) /
			(sprite->dist * cos(sprite->dir)));
		coef = (float)(SCALE * 4) / sprite->height;
		point.x = sprite->dir * (all->map_data->screen_width / 2) / (PI / 6)
					+ all->map_data->screen_width / 2 - sprite->height / 2;
		point.y = all->map_data->screen_height / 2 - sprite->height / 2;
		draw_sprite(all, &point, coef, sprite);
	}
}

void	draw_sprite(t_all *all, t_point *point, float coef, t_sprite *sprite)
{
	char	*color;
	int		x;
	int		y;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->height)
		{
			if (point->x + y < all->map_data->screen_width && y + point->x >= 0)
			{
				color = all->texture_sprite->addr + (((int)(x * coef) *
					all->texture_sprite->line_length) + ((int)(y * coef) *
					(all->texture_sprite->bits_per_pixel / 8)));
				if ((*(unsigned int *)color & 0x00FFFFFF) != 0 && point->y + x >
			0 && point->x + y > 0 && point->x + y < all->map_data->screen_width
				&& point->y + x < all->map_data->screen_height)
					pixel_put(all->params, point->x + y, point->y + x,
						*(unsigned int *)color);
			}
			x++;
		}
		y++;
	}
}
