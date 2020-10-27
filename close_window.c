/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:13:54 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 23:14:40 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_window(t_all *all)
{
	if (all->map_data->north)
		free(all->map_data->north);
	if (all->map_data->south)
		free(all->map_data->south);
	if (all->map_data->east)
		free(all->map_data->east);
	if (all->map_data->west)
		free(all->map_data->west);
	if (all->map_data->sprite)
		free(all->map_data->sprite);
	if (all->d_arr)
		free_int_arr(all->d_arr);
	exit(0);
}
