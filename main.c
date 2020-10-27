/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:44:44 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 16:15:13 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list	*lst;
	t_map	map_data;

	line = NULL;
	lst = NULL;
	init_map_data(&map_data);
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		map_data.screenshot = 1;
	if ((argc < 2 || argc > 3) || (argc == 3 && !map_data.screenshot))
		error(ER_ARG);
	((fd = open(argv[1], O_RDONLY)) <= 0) ? error(ER_OPEN) : 0;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	ft_lstadd_back(&lst, ft_lstnew(line));
	map_data.map = read_map(&lst);
	map_data.head_map = map_data.map;
	get_map_info(map_data.map, &map_data);
	open_window(&map_data);
	free_map_data(&map_data, &lst, map_data.head_map);
	return (0);
}

char	**read_map(t_list **head)
{
	char	**map;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	if (!(map = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char*))))
		error(ER_MALLOC);
	while (tmp)
	{
		if (!(map[i] = ft_strdup(tmp->content)))
			error(ER_MALLOC);
		tmp = tmp->next;
		i++;
	}
	map[i] = 0;
	return (map);
}

void	init_map_data(t_map *map_data)
{
	map_data->floor_color = -1;
	map_data->ceiling_color = -1;
	map_data->screen_height = -1;
	map_data->screen_width = -1;
	map_data->north = NULL;
	map_data->south = NULL;
	map_data->west = NULL;
	map_data->east = NULL;
	map_data->sprite = NULL;
	map_data->screenshot = 0;
}

void	free_map_data(t_map *map_data, t_list **lst, char **map)
{
	if (map)
		free_arr(map);
	if (map_data->north)
		free(map_data->north);
	if (map_data->south)
		free(map_data->south);
	if (map_data->east)
		free(map_data->east);
	if (map_data->west)
		free(map_data->west);
	if (map_data->sprite)
		free(map_data->sprite);
	if (lst || *lst)
		ft_lstclear(lst, &free);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
