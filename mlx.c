/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:51:01 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/04 16:11:40 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx(char **map)
{
	t_params	params;
	t_player	player;
	t_all		all;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, 1200, 800, "CUB3D");
	params.img = mlx_new_image(params.mlx, 1200, 800);
	params.addr = mlx_get_data_addr(params.img, &params.bits_per_pixel, &params.line_length, &params.endian);
	all.params = &params;
	all.player = &player;
	all.map = map;
	print_map(&all);
	print_player(&all);
	mlx_loop_hook(params.mlx, display, &all);
	mlx_loop(params.mlx);
}

void	pixel_put(t_params *params, int x, int y, int color)
{
    char    *dst;

    dst = params->addr + (y * params->line_length + x * (params->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		press_key(int key, t_all *all)
{
	if (key == KEY_A)
	{
		all->player->dir -= 0.1;
		if (all->player->dir < 0)
			all->player->dir += 2 * PI;
	}
	if (key == KEY_D)
	{
		all->player->dir += 0.1;
		if (all->player->dir > 2 * PI)
			all->player->dir -= 2 * PI;
	}
	if (key == KEY_S)
	{
		all->player->x -= cos(all->player->dir) * 4;
		all->player->y -= sin(all->player->dir) * 4;
	}
	if (key == KEY_W)
	{
		all->player->x += cos(all->player->dir) * 4;
		all->player->y += sin(all->player->dir) * 4;
	}
	if (key == KEY_ESC)
		exit(0);
	print_map(all);
	print_player(all);
	cast_rays(all);
	return (0);
}

void	print_square(t_params *params, int x, int y, int color)
{
	t_point	end;

	end.y = (y + 1) * SCALE;
	end.x = (x + 1) * SCALE;
	x *= SCALE;
	y *= SCALE;
	while (y < end.y)
    {
		while (x < end.x)
		{
			pixel_put(params, x, y, color);
			x++;
		}
		x -= SCALE;
		y++;
	}
}

/*
** green	0x43723E
** red		0xE45F42
** beige	0xDAC890
** black	0x000000
*/

void	print_player(t_all *all)
{
	pixel_put(all->params, all->player->x, all->player->y, 0xDAC890);
}

void	print_map(t_all *all)
{
	t_point	point;

	point.y = 0;
	while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			if (all->map[point.y][point.x] == '1')
				print_square(all->params, point.x, point.y, 0x43723E);
			if (all->map[point.y][point.x] == '0' || all->map[point.y][point.x] == '2')
				print_square(all->params, point.x, point.y, 0xE45F42);
			if (all->map[point.y][point.x] == 'N' || all->map[point.y][point.x] == 'S' ||
			all->map[point.y][point.x] == 'W' || all->map[point.y][point.x] == 'E')
			{
				all->player->x = point.x * SCALE + SCALE / 2;
				all->player->y = point.y * SCALE + SCALE / 2;
				all->player->dir = what_dir(all->map[point.y][point.x]);
				all->map[point.y][point.x] = '0';
				print_square(all->params, point.x, point.y, 0xE45F42);
				// printf("%d - %d - %f\n", all->player->x, all->player->y, all->player->dir);
			}
			point.x++;
		}
		point.y++;
	}
}

int		display(t_all *all)
{
	mlx_hook(all->params->win, 2, 1L << 0, press_key, all);
	mlx_put_image_to_window(all->params->mlx, all->params->win, all->params->img, 10, 10);
	return (0);
}

float	what_dir(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (3 * PI / 2);
	if (c == 'W')
		return (PI);
	if (c == 'S')
		return (PI / 2);
	return (0);
}