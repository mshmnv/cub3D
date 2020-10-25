/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:53:18 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/25 11:01:49 by lbagg            ###   ########.fr       */
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
		error(er_malloc);
	while (tmp)
	{
		if (!(map[i] = ft_strdup(tmp->content)))
			error(er_malloc);
		tmp = tmp->next;
		i++;
	}
	map[i] = 0;
	return (map);
}

t_map	get_map_info(char **map, int *start_map)
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
			// else if (!symb[s + 1] && map[i][0] != '1')
				// error(er_map);
			s++;
		}
		i++;
	}
	return (map_data);
}

void	what_color(char **el, t_map *map_data, char key)
{
	if (!el[0] || !el[1] || !el[2])
		error(er_color);
	if ((ft_atoi(el[0]) >= 0 && ft_atoi(el[0]) <= 255) 
	&& (ft_atoi(el[1]) >= 0 && ft_atoi(el[1]) <= 255)
	&& (ft_atoi(el[2])>= 0 && ft_atoi(el[2]) <= 255))
	{	
		if (key == 'f')
			map_data->floor_color = (ft_atoi(el[0]) << 16) + (ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
		if (key == 'c')
			map_data->ceiling_color = (ft_atoi(el[0]) << 16) + (ft_atoi(el[1]) << 8) + ft_atoi(el[2]);
	}
	else
		error(er_color);
}

t_map	into_struct(char *map, char *symb)
{
	t_map	map_data;
	char	**el;

	if (into_struct_2(map, symb, &map_data))
		return (map_data);
	else if (ft_strncmp(symb, "F", 2) == 0)
	{
		if (map_data.floor_color)
			error(er_map);
		el = ft_split(map, ',');
		what_color(el, &map_data, 'f');
		free(el[2]);
		free(el[1]);
		free(el[0]);
		free(el);
	}
	else if (ft_strncmp(symb, "C", 2) == 0)
	{
		el = ft_split(map, ',');
		what_color(el, &map_data, 'c');
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
			error(er_res_size);
		if (((*map_data).screen_width = ft_atoi(el[1])) <= 0)	//// ? > screen resolution
			error(er_res_size);
		free(el[1]);
		free(el[0]);
	}
	if (ft_strncmp(symb, "NO", 2) == 0)
		((*map_data).north = ft_strdup(map)) ? 0 : error(er_malloc);
	else if (ft_strncmp(symb, "SO", 2) == 0)
		((*map_data).south = ft_strdup(map)) ? 0 : error(er_malloc);
	else if (ft_strncmp(symb, "WE", 2) == 0)
		((*map_data).west = ft_strdup(map)) ? 0 : error(er_malloc);
	else if (ft_strncmp(symb, "EA", 2) == 0)
		((*map_data).east = ft_strdup(map)) ? 0 : error(er_malloc);
	else if (ft_strncmp(symb, "S", 2) == 0)
		((*map_data).sprite = ft_strdup(map)) ? 0 : error(er_malloc);
	else
		return (0);
	return (1);
}
