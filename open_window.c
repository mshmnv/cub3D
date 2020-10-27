/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:51:01 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 14:00:01 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_window(t_map *map_data)
{
	t_texture	texture[5];
	t_player	player;
	t_all		all;
	t_data		data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, map_data->screen_width,
		map_data->screen_height, "CUB3D");
	data.img = mlx_new_image(data.mlx, map_data->screen_width,
		map_data->screen_height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp,
		&data.line_len, &data.endian);
	all.data = &data;
	all.player = &player;
	texture_structs(&all, map_data, texture);
	all.map_data = map_data;
	find_player(&all, map_data->map);
	find_sprites(&all);
	color_screen(&all);
	cast_rays(&all);
	print_sprites(&all);
	(all.map_data->screenshot) ? screenshot(&all) : 0;
	mlx_loop_hook(data.mlx, display, &all);
	mlx_hook(all.data->win, 2, 1L << 0, press_key, &all);
	mlx_loop(data.mlx);
}

void	texture_structs(t_all *all, t_map *map_data, t_texture *texture)
{
	(!(texture[0].img = mlx_xpm_file_to_image(all->data->mlx, map_data->north,
		&texture[0].width, &texture[0].height))) ? error(ER_TEXT_PATH) : 0;
	texture[0].addr = mlx_get_data_addr(texture[0].img,
	&texture[0].bpp, &texture[0].line_len, &texture[0].endian);
	(!(texture[1].img = mlx_xpm_file_to_image(all->data->mlx, map_data->south,
		&texture[1].width, &texture[1].height))) ? error(ER_TEXT_PATH) : 0;
	texture[1].addr = mlx_get_data_addr(texture[1].img,
		&texture[1].bpp, &texture[1].line_len, &texture[1].endian);
	(!(texture[2].img = mlx_xpm_file_to_image(all->data->mlx, map_data->west,
	&texture[2].width, &texture[2].height))) ? error(ER_TEXT_PATH) : 0;
	texture[2].addr = mlx_get_data_addr(texture[2].img,
		&texture[2].bpp, &texture[2].line_len, &texture[2].endian);
	(!(texture[3].img = mlx_xpm_file_to_image(all->data->mlx, map_data->east,
		&texture[3].width, &texture[3].height))) ? error(ER_TEXT_PATH) : 0;
	texture[3].addr = mlx_get_data_addr(texture[3].img,
		&texture[3].bpp, &texture[3].line_len, &texture[3].endian);
	(!(texture[4].img = mlx_xpm_file_to_image(all->data->mlx, map_data->sprite,
		&texture[4].width, &texture[4].height))) ? error(ER_TEXT_PATH) : 0;
	texture[4].addr = mlx_get_data_addr(texture[4].img,
		&texture[4].bpp, &texture[4].line_len, &texture[4].endian);
	all->text_no = &texture[0];
	all->text_so = &texture[1];
	all->text_we = &texture[2];
	all->text_ea = &texture[3];
	all->texture_sprite = &texture[4];
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
	(key == KEY_L) ? (all->player->dir = fix_ray(all->player->dir - 0.1)) : 0;
	(key == KEY_R) ? (all->player->dir = fix_ray(all->player->dir + 0.1)) : 0;
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	find_player(t_all *all, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				all->player->x = x * SCALE + SCALE / 2;
				all->player->y = y * SCALE + SCALE / 2;
				(map[y][x] == 'E') ? all->player->dir = 0 : 0;
				(map[y][x] == 'N') ? all->player->dir = 3 * M_PI_2 : 0;
				(map[y][x] == 'W') ? all->player->dir = M_PI : 0;
				(map[y][x] == 'S') ? all->player->dir = M_PI_2 : 0;
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

int		display(t_all *all)
{
	color_screen(all);
	cast_rays(all);
	print_sprites(all);
	mlx_put_image_to_window(all->data->mlx, all->data->win,
		all->data->img, 0, 0);
	mlx_do_sync(all->data->mlx);
	return (0);
}
