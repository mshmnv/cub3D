/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:29:00 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/05 10:35:10 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_vertical(t_all *all, int start, int end, int ray_x)
{
	while (start <= end)
	{
		pixel_put(all->params, ray_x, start, 0xDAC890);
		start++;
	}
}

void	print_3d(t_all *all, float dist, int ray_x)
{
	int	line_height;
	int	start;
	int end;

	line_height = (SCALE * 320) / dist;
	if (line_height > 320)
		line_height = 320;
	start = 160 - line_height / 2;
	if (start < 0)
		start = 0;
	end = 160 + line_height / 2;
	if (end >= 320)
		end = 320 - 1;
	print_vertical(all, start, end, ray_x);
}