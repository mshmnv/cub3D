/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:09:09 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 14:00:19 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_sprites(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	all->sprites = NULL;
	while (all->map_data->map[y])
	{
		x = 0;
		while (all->map_data->map[y][x])
		{
			if (all->map_data->map[y][x] == '2')
			{
				add_back_sprite(&all->sprites, new_sprite(x, y));
			}
			x++;
		}
		y++;
	}
	sort_sprites(all);
}

void		add_back_sprite(t_sprite **sprite, t_sprite *new)
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

t_sprite	*new_sprite(float x, float y)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite*)malloc(sizeof(t_sprite))))
		error(ER_MALLOC);
	sprite->x = x * SCALE + SCALE / 2;
	sprite->y = y * SCALE + SCALE / 2;
	sprite->dist = 0;
	sprite->dir = 0;
	sprite->height = 0;
	sprite->next = NULL;
	return (sprite);
}

void		sort_sprites(t_all *all)
{
	t_sprite	*tmp;
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

void		swap_sprites(t_sprite **head, t_sprite *first, t_sprite *second)
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
