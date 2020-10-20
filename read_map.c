/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:53:18 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/20 15:36:47 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_map(char *line, t_list **head)
{
	char	**map;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	if (!(map = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char*))))
		error('m');
	while (tmp)
	{
		if (!(map[i] = ft_strdup(tmp->content)))
			error('m');
		tmp = tmp->next;
		i++;
	}
	map[i] = 0;
	return (map);
}

t_map	get_map_info(char **map)
{
	int		i;
	int		s;
	t_map	map_data;
	char	*symb[]= {"R", "NO", "SO", "WE", "EA", "S", "F", "C", 0};

	i = 0;
	while (map[i])
	{
		s = 0;
		while (symb[s])
		{
			if (ft_strnstr(map[i], symb[s], ft_strlen(symb[s])))
			{
				map[i] += ft_strlen(symb[s]) + 1;
				map_data = into_struct(map[i], symb[s]);
				break ;
			}
			s++;
		}
		i++;
	}
	// printf("'%d''%d'\n", map_data.resolution[0], map_data.resolution[1]);
	// printf("'%s'\n'%s'\n'%s'\n'%s'\n", map_data.north, map_data.south, map_data.west, map_data.east);
	// printf("'%s'\n", map_data.sprite);
	// printf("'%d'\n", map_data.floor_color);
	// printf("'%d'\n", map_data.ceiling_color);
	return (map_data);
}

t_map	into_struct(char *map, char *symb)
{
	t_map	map_data;
	char	**el;

	if (into_struct_2(map, symb, &map_data))
		return (map_data);
	if (ft_strncmp(symb, "F", 2) == 0)
	{
		el = ft_split(map, ',');
		map_data.floor_color = (ft_atoi(el[0]) << 16) + (ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
		free(el[2]);
		free(el[1]);
		free(el[0]);
		free(el);
	}
	else if (ft_strncmp(symb, "C", 2) == 0)
	{
		el = ft_split(map, ',');
		map_data.ceiling_color = (ft_atoi(el[0]) << 16) + (ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
		free(el[2]);
		free(el[1]);
		free(el[0]);
		free(el);
	}
	return (map_data);
}

int	into_struct_2(char *map, char *symb, t_map *map_data)
{
	char	**el;

	if (ft_strncmp(symb, "R", 1) == 0)
	{
		el = ft_split(map, ' ');
		if (((*map_data).screen_height = ft_atoi(el[0])) <= 0)   //// ? > screen resolution
			error('r');
		if (((*map_data).screen_width = ft_atoi(el[1])) <= 0)	//// ? > screen resolution
			error('r');
		free(el[1]);
		free(el[0]);
	}
	if (ft_strncmp(symb, "NO", 2) == 0)
		((*map_data).north = ft_strdup(map)) ? 0 : error('m');
	else if (ft_strncmp(symb, "SO", 2) == 0)
		((*map_data).south = ft_strdup(map)) ? 0 : error('m');
	else if (ft_strncmp(symb, "WE", 2) == 0)
		((*map_data).west = ft_strdup(map)) ? 0 : error('m');
	else if (ft_strncmp(symb, "EA", 2) == 0)
		((*map_data).east = ft_strdup(map)) ? 0 : error('m');
	else if (ft_strncmp(symb, "S", 2) == 0)
		((*map_data).sprite = ft_strdup(map)) ? 0 : error('m');
	else
		return (0);
	return (1);
}
