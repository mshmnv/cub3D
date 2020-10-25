/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:44:44 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/25 11:08:31 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char ***map, t_map	*map_data, t_list **lst)
{
	while (**map)
	{
		free(**map);
		(*map)++;
	}
	if (*map)
		free(*map);
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
	if (lst)
		ft_lstclear(lst, &free);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list	*lst;
	char	**map;
	t_map	map_data;
	int		start_map;

	if (argc != 2 && (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0))
		error(er_arg);
	if (!(fd = open(argv[1], O_RDONLY)))
		error(er_open);
	line = NULL;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	ft_lstadd_back(&lst, ft_lstnew(line));
	map = read_map(line, &lst);
	map_data = get_map_info(map, &start_map);
	map_data.screenshot = 0;
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		map_data.screenshot = 1;
	mlx(map + 10, &map_data);
	free_map(&map, &map_data, &lst);
	return (0);
}
