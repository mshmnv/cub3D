/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:53:18 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 22:57:47 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_info(char **map, t_map *map_data)
{
	int		i;
	char	**str;

	i = -1;
	while (map[++i])
	{
		str = ft_split(map[i], ' ');
		if (str[0] && str[1] && str[2])
			into_struct_res(str[1], str[2], str[0], map_data);
		else if (str[0] && str[1])
			into_struct(str[1], str[0], map_data);
		else if (str[0] && !str[1] && (str[0][0] == '1' || str[0][0] == ' '))
		{
			valid_map(map + i);
			map_data->map += i;
			free_arr(str);
			map_data->flag_map = 1;
			break ;
		}
		else if (str[0] && str[0][0])
			error(ER_MAP);
		free_arr(str);
	}
	valid_path_text(map_data);
	valid_keys(map_data);
}

void	what_color(char **el, t_map *map_data, char key)
{
	if (!el[0] || !el[1] || !el[2])
		error(ER_COLOR);
	if ((ft_atoi(el[0]) >= 0 && ft_atoi(el[0]) <= 255)
	&& (ft_atoi(el[1]) >= 0 && ft_atoi(el[1]) <= 255)
	&& (ft_atoi(el[2]) >= 0 && ft_atoi(el[2]) <= 255))
	{
		if (key == 'f')
			map_data->floor_color = (ft_atoi(el[0]) << 16) +
			(ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
		if (key == 'c')
			map_data->ceiling_color = (ft_atoi(el[0]) << 16) +
			(ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
	}
	else
		error(ER_COLOR);
}

void	into_struct(char *value, char *key, t_map *map_data)
{
	char	**el;

	if (ft_strncmp(key, "F", 2) == 0)
	{
		(map_data->floor_color != -1) ? error(ER_MAP) : 0;
		el = ft_split(value, ',');
		what_color(el, map_data, 'f');
		free_arr(el);
	}
	else if (ft_strncmp(key, "C", 2) == 0)
	{
		el = ft_split(value, ',');
		(map_data->ceiling_color != -1) ? error(ER_MAP) : 0;
		what_color(el, map_data, 'c');
		free_arr(el);
	}
	into_struct_2(value, key, map_data);
}

void	into_struct_res(char *width, char *height, char *key, t_map *map_data)
{
	if (ft_strncmp(key, "R", 1) == 0)
	{
		if (map_data->screen_height != -1 && map_data->screen_width != -1)
			error(ER_MAP);
		map_data->screen_width = ft_atoi(width);
		map_data->screen_height = ft_atoi(height);
		if (map_data->screen_height <= 100 || map_data->screen_width <= 100)
			error(ER_RES_SIZE);
		if (map_data->screen_height > 1440)
			map_data->screen_height = 1440;
		if (map_data->screen_width > 2560)
			map_data->screen_width = 2560;
	}
}

void	into_struct_2(char *value, char *key, t_map *map_data)
{
	if (ft_strncmp(key, "NO", 2) == 0)
	{
		(map_data->north != NULL) ? error(ER_MAP) : 0;
		(map_data->north = ft_strdup(value)) ? 0 : error(ER_MALLOC);
	}
	else if (ft_strncmp(key, "SO", 2) == 0)
	{
		(map_data->south != NULL) ? error(ER_MAP) : 0;
		(map_data->south = ft_strdup(value)) ? 0 : error(ER_MALLOC);
	}
	else if (ft_strncmp(key, "WE", 2) == 0)
	{
		(map_data->west != NULL) ? error(ER_MAP) : 0;
		(map_data->west = ft_strdup(value)) ? 0 : error(ER_MALLOC);
	}
	else if (ft_strncmp(key, "EA", 2) == 0)
	{
		(map_data->east != NULL) ? error(ER_MAP) : 0;
		(map_data->east = ft_strdup(value)) ? 0 : error(ER_MALLOC);
	}
	else if (ft_strncmp(key, "S", 2) == 0)
	{
		(map_data->sprite != NULL) ? error(ER_MAP) : 0;
		(map_data->sprite = ft_strdup(value)) ? 0 : error(ER_MALLOC);
	}
}
