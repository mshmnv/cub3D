/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:51:16 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/25 20:26:47 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define SCALE				100
# define KEY_A				0
# define KEY_W				13
# define KEY_D				2
# define KEY_S				1
# define KEY_ESC			53
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define PI					3.1415926535
# define er_open			0
# define er_arg				1
# define er_malloc			2
# define er_text_path		3
# define er_res_size		4
# define er_more_players	5
# define er_screenshot		6
# define er_map				7
# define er_color			8


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

typedef struct		s_sprite
{
	float			x;
	float			y;
	int				dist;
	float			dir;
	int				height;
	struct s_sprite	*next;
}					t_sprite;


typedef struct	s_map
{
	int			screen_height;
	int			screen_width;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	int			floor_color;
	int			ceiling_color;
	int			screenshot;
}				t_map;

typedef struct s_all
{
	t_params	*params;
	t_player	*player;
	t_texture	*texture_no;
	t_texture	*texture_so;
	t_texture	*texture_we;
	t_texture	*texture_ea;
	t_texture	*texture_sprite;
	t_sprite	*sprites;
	char		**map;
	t_map		*map_data;
}				t_all;

// main
char			**read_map(t_list **head);
void			init_map_data(t_map *map_data);
void			free_map_data(char ***map, t_map *map_data, t_list **lst);
// read_map
void			get_map_info(char **map, t_map *map_data, int *start_map);
void			into_struct(char *value, char *key, t_map *map_data);
void			into_struct_res(char *width, char *height, char *key, t_map *map_data);
void			into_struct_2(char *value, char *key, t_map *map_data);
// mlx
void			mlx(char **map, t_map *map_data);
void			texture_structs(t_all *all, t_map *map_data, t_texture *texture);
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
void			print_3d(t_all *all, float dist, int num_ray, int text_x, t_texture *texture);
float			fix_ray(float ray);
void			color_screen(t_all *all);
// find_sprites
void			find_sprites(t_all *all);
t_sprite		*new_sprite(float x, float y);
void			add_back_sprite(t_sprite **sprite, t_sprite *new);
void			sort_sprites(t_all *all);
void			swap_sprites(t_sprite **head, t_sprite *first, t_sprite * second);
// print_sprites
void			print_sprites(t_all *all);
void			culc_sprite(t_all *all, t_sprite *sprite);
int				no_walls(t_all *all, t_sprite *tmp);
void			draw_sprite(t_all *all, t_point *point, float coef, t_sprite *sprite);
// error
void			error(int key);
// screenshot
void			screenshot(t_all *all);
#endif