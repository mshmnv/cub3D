/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:51:16 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/08 19:24:52 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define SCALE		16
# define KEY_A		0
# define KEY_W		13
# define KEY_D		2
# define KEY_S		1
# define KEY_ESC	53
# define KEY_LEFT	123
# define KEY_RIGHT	124

# define SCREEN_HEIGHT 800
# define SCREEN_WIDTH 1200

# define PI 3.1415926535

# include <stdio.h>

typedef struct	s_player
{
	float		x;
	float		y;
	float		dir;
}				t_player;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_params
{
	void		*mlx;
	void		*win;
	void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;

}				t_params;

typedef struct	s_texture
{
	void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_all
{
	t_params	*params;
	t_player	*player;
	t_texture	*texture;
	char		**map;
}				t_all;

typedef struct	s_map
{
	int			resolution[2];
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	int			floor[3];
	int			ceilling[3];
}				t_map;

char			**read_map(char *line, t_list **head);
t_map			get_map_info(char **map);
t_map			into_struct(char *map, char *symb);
int				into_struct_2(char *map, char *symb, t_map *map_data);

// mlx
void			mlx(char **map);
void			pixel_put(t_params *params, int x, int y, int color);
void			print_square(t_params *params, int x, int y, int color);
void			print_map(t_all *all);
int				press_key(int key, t_all *all);
int				display(t_all *all);
float			what_dir(char c);

// rays
void			cast_rays(t_all *all);
float			vertic_length(t_player *ray, t_all *all);
float			horizont_length(t_player *ray, t_all *all);
void			print_line(t_all *all, int length, float dir);
int				height_len(char **map);

//	print_3d
void			print_3d(t_all *all, float dist, int num_ray, t_player *ray);
float			fix_ray(float ray);
void			color_screen(t_all *all);
#endif