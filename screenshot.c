/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:34:47 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 14:00:43 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_data *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	color = *(int*)dst;
	return (color);
}

static void	int_to_char(int i, unsigned char *arr)
{
	arr[0] = (unsigned char)(i);
	arr[1] = (unsigned char)(i >> 8);
	arr[2] = (unsigned char)(i >> 16);
	arr[3] = (unsigned char)(i >> 24);
}

static void	print_color(t_all *all, int fd)
{
	int		i;
	int		j;
	int		color;

	i = all->map_data->screen_height - 1;
	while (0 <= i)
	{
		j = 0;
		while (j < all->map_data->screen_width)
		{
			color = get_color(all->data, j, i);
			write(fd, &color, 3);
			j++;
		}
		i--;
	}
}

void		screenshot(t_all *all)
{
	int				fd;
	int				filesize;
	unsigned char	arr[54];
	int				count;

	filesize = ((all->map_data->screen_height * all->map_data->screen_width)
			* 4) + 54;
	((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC |
		O_APPEND, 0666)) < 0) ? error(ER_SCREENSHOT) : 0;
	count = 0;
	while (count < 54)
		arr[count++] = 0;
	arr[0] = 'B';
	arr[1] = 'M';
	int_to_char(filesize, &arr[2]);
	arr[10] = (unsigned char)(54);
	arr[14] = (unsigned char)(40);
	int_to_char(all->map_data->screen_width, &arr[18]);
	int_to_char(all->map_data->screen_height, &arr[22]);
	arr[26] = (unsigned char)(1);
	arr[28] = (unsigned char)(24);
	write(fd, arr, 54);
	print_color(all, fd);
	close(fd);
	exit(0);
}
