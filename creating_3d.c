/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/05 19:05:04 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_vertical(t_all *all, int num_ray,)
// {
// 	while ()
// }

void	print_3d(t_all *all, float dist, int num_ray)
{
	int	line_height;
	int	line_offset;
	int	end;

	line_height = (SCALE * 500) / dist;
	if (line_height > 500)
		line_height = 500;
	line_offset = 250 - line_height / 2;
	end = line_offset + line_height;
	while (line_offset <= end)
	{
		pixel_put(all->params, num_ray  + 500, line_offset, 0xDAC890);
		line_offset++;
	}
}