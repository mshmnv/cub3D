/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:09:09 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/24 22:01:52 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		no_walls(t_all *all, t_sprite *tmp)
{
	int 	i;
	float	x;
	float	y;

	x = all->player->x;
	y = all->player->y;
	i = 0;
	while (i <= tmp->dist)
	{
		if (all->map[(int)(y + i * sin(tmp->dir))/ SCALE][(int)(x + i * cos(tmp->dir))/SCALE] == '1')
			return (0);
		i++;
	}
	return (1);
}

void	swap_sprites(t_sprite **head, t_sprite *first, t_sprite * second)
{
	t_sprite	*root;
	t_sprite	*tmp;

	root = *head;
	if (root == first)
	{
		tmp = second->next;
		second->next = first;
		first->next = tmp;
		(*head) = second;
	}
	else
	{
		while (root->next != first)
			root = root->next;
		tmp = second->next;
		second->next = first;
		first->next = tmp;
		root->next = second;
	}
}

void	sort_sprites(t_all *all)
{
	t_sprite	*tmp;
	t_sprite	*prev;
	int			change;

	change = 1;
	while (change)
	{
		change = 0;
		tmp = all->sprites;
		while (tmp->next)
		{
			if (tmp->dist < tmp->next->dist)
			{
				swap_sprites(&all->sprites, tmp, tmp->next);
				change = 1;
			}
			else
				tmp = tmp->next;
		}

	}
}

void	print_sprites(t_all *all)
{
	t_sprite	*tmp;

	sort_sprites(all);
	tmp = all->sprites;
	while (tmp)
	{
		tmp->dist = sqrt(pow(all->player->x - tmp->x, 2) + pow(all->player->y - tmp->y, 2));
		tmp->dir = fix_ray(atan2(tmp->y - all->player->y, tmp->x - all->player->x));
		tmp = tmp->next;
	}
	tmp = all->sprites;
	while (tmp != NULL)
	{
		if(no_walls(all, tmp))
			culc_sprite(all, tmp);
		tmp = tmp->next;
	}
}

void	draw_sprite(t_all *all, int sprite_x, int sprite_y, float coef, t_sprite *sprite)
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
			if (sprite_x + y < all->map_data->screen_width && y + sprite_x >= 0)
			{
				color = all->texture_sprite->addr + (((int)(x  * coef) * all->texture_sprite->line_length)
				+ ((int)(y * coef) * (all->texture_sprite->bits_per_pixel / 8)));
				if ((*(unsigned int *)color & 0x00FFFFFF) != 0 && sprite_y + x > 0&& sprite_x + y > 0 && sprite_x + y < all->map_data->screen_width
				&& sprite_y + x < all->map_data->screen_height)
					pixel_put(all->params, sprite_x + y, sprite_y + x, *(unsigned int *)color);
			}
			x++;
		}
		y++;
	}
}

void	culc_sprite(t_all *all, t_sprite *sprite)
{
	int 	proj_plane;
	float	coef;
	int		sprite_x;
	int		sprite_y;

	// sprite->dir = atan2(sprite->y - all->player->y, sprite->x - all->player->x);
	// sprite->dir = fix_ray(sprite->dir);
	sprite->dir = sprite->dir - all->player->dir;
	if (sprite->dir > - PI / 6 && sprite->dir < PI / 6)
	{
		pixel_put(all->params, sprite->x / SCALE * 16, sprite->y / SCALE * 16, 0xFFFFFF);
		proj_plane = all->map_data->screen_width / (2 * tan(PI / 6));
		sprite->height = fabs((SCALE * proj_plane) / (sprite->dist * cos(sprite->dir)));
		coef = (float)(SCALE * 4) / sprite->height;
		sprite_x = sprite->dir * (all->map_data->screen_width / 2) / (PI / 6)
					+ all->map_data->screen_width / 2 - sprite->height / 2;
		sprite_y = all->map_data->screen_height / 2 - sprite->height / 2;
		draw_sprite(all, sprite_x, sprite_y, coef, sprite);
	}
}

t_sprite	*new_sprite(t_all *all, float x, float y)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite*)malloc(sizeof(t_sprite))))
		error(er_malloc);
	sprite->x = x * SCALE + SCALE / 2;
	sprite->y = y * SCALE + SCALE / 2;
	sprite->dist = 0;
	sprite->dir = 0;
	sprite->height = 0;
	sprite->next = NULL;
	return (sprite);
}

void	add_back_sprite(t_sprite **sprite, t_sprite *new)
{
	t_sprite	*head;

	head = *sprite;
	if (head == NULL)
		*sprite = new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
}

void	find_sprites(t_all *all)
{
	int			x;
	int 		y;

	y = 0;
	all->sprites = NULL;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == '2')
			{
				add_back_sprite(&all->sprites, new_sprite(all, x, y));
			}
			x++;
		}
		y++;
	}
}
