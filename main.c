/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:44:44 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/20 12:05:10 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char ***map, t_map	*map_data)
{
	while (**map)
	{
		free(**map);
		(*map)++;
	}
	free(*map);
	free(map_data->north);
	free(map_data->south);
	free(map_data->east);
	free(map_data->west);
	free(map_data->sprite);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list	*lst;
	char	**map;
	t_map	map_data;

	if (argc != 2 && argc != 3)
		error('a');
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	ft_lstadd_back(&lst, ft_lstnew(line));
	map = read_map(line, &lst);
	ft_lstclear(&lst, &free);
	map_data = get_map_info(map);
/*
** 	is map valid ?
**  map + strings till the beginning of the map
*/
	mlx(map + 10, &map_data);
	free_map(&map, &map_data);
	return (0);
}
