/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:51:03 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 16:20:31 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_map(char **map)
{
	int	i;
	int	j;
	int player;

	i = 0;
	j = 0;
	player = 0;
	check_frame(map[i], &j);
	while (map[++i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		(map[i][j] != '1') ? error(ER_MAP) : 0;
		while (map[i][j] && ft_strchr("012NSWE", map[i][j]))
		{
			if (ft_strchr("NSWE", map[i][j]))
				(++player > 1) ? error(ER_MORE_PLAYER) : 0;
			j++;
		}
		((map[i][j] != '\0') || (map[i][j - 1] != '1')) ? error(ER_MAP) : 0;
	}
	j = 0;
	check_frame(map[i - 1], &j);
	(!player) ? error(ER_MAP) : 0;
}

void	check_frame(char *str, int *j)
{
	while (str[*j] == ' ')
		(*j)++;
	while (str[*j] == '1')
		(*j)++;
	if (str[*j] != '\0')
		error(ER_MAP);
}

void	valid_keys(t_map *map_data)
{
	if (map_data->floor_color == -1 || map_data->ceiling_color == -1
	|| map_data->screen_height == -1 || map_data->screen_width == -1
	|| !map_data->north || !map_data->south || !map_data->east
	|| !map_data->west || !map_data->sprite)
		error(ER_MAP);
}

void	valid_path_text(t_map *map_data)
{
	(!ft_strncmp(map_data->east, map_data->west, ft_strlen(map_data->east)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->east, map_data->west, ft_strlen(map_data->west)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->east, map_data->north, ft_strlen(map_data->north)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->east, map_data->south, ft_strlen(map_data->east)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->east, map_data->south, ft_strlen(map_data->south)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->west, map_data->north, ft_strlen(map_data->west)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->west, map_data->north, ft_strlen(map_data->north)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->west, map_data->south, ft_strlen(map_data->west)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->west, map_data->south, ft_strlen(map_data->south)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->north, map_data->south, ft_strlen(map_data->north)))
	? error(ER_TEXT_PATH) : 0;
	(!ft_strncmp(map_data->north, map_data->south, ft_strlen(map_data->south)))
	? error(ER_TEXT_PATH) : 0;
}
