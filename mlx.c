/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:51:01 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/24 22:04:55 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print(t_all *all)
{
	color_screen(all);
	print_map(all);
	cast_rays(all);
	print_map(all);
	print_sprites(all);
}

void	texture_structs(t_all *all, t_map *map_data, t_texture *texture)
{
	if (!(texture[0].img = mlx_xpm_file_to_image(all->params->mlx, map_data->north, &texture[0].width, &texture[0].height)))
			error(er_text_path);
	texture[0].addr = mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].line_length, &texture[0].endian);
	if (!(texture[1].img = mlx_xpm_file_to_image(all->params->mlx, map_data->south, &texture[1].width, &texture[1].height)))
			error(er_text_path);
	texture[1].addr = mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel, &texture[1].line_length, &texture[1].endian);
	if (!(texture[2].img = mlx_xpm_file_to_image(all->params->mlx, map_data->west, &texture[2].width, &texture[2].height)))
			error(er_text_path);
	texture[2].addr = mlx_get_data_addr(texture[2].img, &texture[2].bits_per_pixel, &texture[2].line_length, &texture[2].endian);
	if (!(texture[3].img = mlx_xpm_file_to_image(all->params->mlx, map_data->east, &texture[3].width, &texture[3].height)))
			error(er_text_path);
	texture[3].addr = mlx_get_data_addr(texture[3].img, &texture[3].bits_per_pixel, &texture[3].line_length, &texture[3].endian);
	if (!(texture[4].img = mlx_xpm_file_to_image(all->params->mlx, map_data->sprite, &texture[4].width, &texture[4].height)))
		error(er_text_path);
	texture[4].addr = mlx_get_data_addr(texture[4].img, &texture[4].bits_per_pixel, &texture[4].line_length, &texture[4].endian);
	all->texture_no = &texture[0];
	all->texture_so = &texture[1];
	all->texture_we = &texture[2];
	all->texture_ea = &texture[3];
	all->texture_sprite = &texture[4];
}

void	mlx(char **map, t_map	*map_data)
{
	t_texture	texture[5];
	t_player	player;
	t_all		all;
	t_params	params;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, map_data->screen_width, map_data->screen_height, "CUB3D");
	params.img = mlx_new_image(params.mlx, map_data->screen_width, map_data->screen_height);
	params.addr = mlx_get_data_addr(params.img, &params.bits_per_pixel, &params.line_length, &params.endian);
	all.params = &params;
	all.player = &player;
	texture_structs(&all, map_data, texture);
	all.map = map;
	all.map_data = map_data;
	print_map(&all);
	find_sprites(&all);	
	print(&all);
	if (all.map_data->screenshot)
		screenshot(&all);
	mlx_loop_hook(params.mlx, display, &all);
	mlx_hook(all.params->win, 2, 1L << 0, press_key, &all);
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
		all->player->x += sin(all->player->dir) * 4;
		all->player->y -= cos(all->player->dir) * 4;
	}
	if (key == KEY_D)
	{
		all->player->x -= sin(all->player->dir) * 4;
		all->player->y += cos(all->player->dir) * 4;
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
	(key == KEY_LEFT) ? (all->player->dir = fix_ray(all->player->dir - 0.1)) : 0;
	(key == KEY_RIGHT) ? (all->player->dir = fix_ray(all->player->dir + 0.1)) : 0;
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	print_square(t_params *params, int x, int y, int color)
{
	t_point	end;

	end.y = (y + 1) * 16;
	end.x = (x + 1) * 16;
	x *= 16;
	y *= 16;
	while (y < end.y)
    {
		while (x < end.x)
		{
			pixel_put(params, x, y, color);
			x++;
		}
		x -= 16;
		y++;
	}
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
			else if (all->map[point.y][point.x] == '2')
				print_square(all->params, point.x, point.y, 0x000000);
			else if (all->map[point.y][point.x] == 'N' || all->map[point.y][point.x] == 'S' ||
			all->map[point.y][point.x] == 'W' || all->map[point.y][point.x] == 'E')
			{
				all->player->x = point.x * SCALE + SCALE / 2;
				all->player->y = point.y * SCALE + SCALE / 2;
				all->player->dir = what_dir(all->map[point.y][point.x]);
				all->map[point.y][point.x] = '0';
				print_square(all->params, point.x, point.y, 0xE45F42);
			}
			point.x++;
		}
		point.y++;
	}
}

int		display(t_all *all)
{
	color_screen(all);
	print_map(all);
	cast_rays(all);
	print_map(all);
	print_sprites(all);
	mlx_put_image_to_window(all->params->mlx, all->params->win, all->params->img, 0, 0);
	mlx_do_sync(all->params->mlx);
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