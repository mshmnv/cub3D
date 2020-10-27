/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:12:43 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 22:16:03 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_arr(t_all *all)
{
	int i;
	int	j;

	i = -1;
	if (all->d_arr == NULL)
	{
		all->d_arr = (int**)malloc(sizeof(int*) *
		(all->map_data->screen_height + 1));
		while (++i < all->map_data->screen_height)
			all->d_arr[i] = (int*)malloc(sizeof(int) *
				(all->map_data->screen_width + 1));
		all->d_arr[i] = 0;
	}
	else
	{
		while (++i < all->map_data->screen_height)
		{
			j = -1;
			while (++j < all->map_data->screen_width)
				all->d_arr[i][j] = 0;
		}
	}
}

void	free_int_arr(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
