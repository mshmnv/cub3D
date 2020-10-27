/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 10:05:26 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 21:16:56 by lbagg            ###   ########.fr       */
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
		culc_sprite(all, tmp);
		tmp = tmp->next;
	}
}

void	culc_sprite(t_all *all, t_sprite *sprite)
{
	int		proj_plane;
	float	coef;
	t_point	point;

	sprite->dir = sprite->dir - all->player->dir;
	if (sprite->dir > -M_PI / 6 && sprite->dir < M_PI / 6)
	{
		proj_plane = all->map_data->screen_width / (2 * tan(M_PI / 6));
		sprite->height = fabs((SCALE * proj_plane) /
			(sprite->dist * cos(sprite->dir)));
		coef = (float)(SCALE * 4) / sprite->height;
		point.x = sprite->dir * (all->map_data->screen_width / 2) / (M_PI / 6)
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

	y = -1;
	while (++y < sprite->height)
	{
		x = 0;
		while (++x < sprite->height)
		{
			if ((point->x + y < all->map_data->screen_width && y + point->x
			>= 0) && (all->d_arr[point->y + x][point->x + y] > sprite->dist ||
			!all->d_arr[point->y + x][point->x + y]))
			{
				color = all->texture_sprite->addr + (((int)(x * coef) *
					all->texture_sprite->line_len) + ((int)(y * coef) *
					(all->texture_sprite->bpp / 8)));
				if ((*(unsigned int *)color & 0x00FFFFFF) != 0 && point->y + x >
			0 && point->x + y > 0 && point->x + y < all->map_data->screen_width
				&& point->y + x < all->map_data->screen_height)
					pixel_put(all->data, point->x + y, point->y + x,
						*(unsigned int *)color);
			}
		}
	}
}
