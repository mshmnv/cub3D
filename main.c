/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:44:44 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/19 14:47:23 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list	*lst;
	char	**map;
	t_map	map_data;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 1);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	ft_lstadd_back(&lst, ft_lstnew(line));
	map = read_map(line, &lst);
	map_data = get_map_info(map);
/*
** 	is map valid ?
**  here will be func to check it
**  map + strings till the beginning of the map
*/
	mlx(map += 10, &map_data);
	return (0);
}
