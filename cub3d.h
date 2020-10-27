/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:51:16 by lbagg             #+#    #+#             */
/*   Updated: 2020/10/27 16:01:30 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define SCALE			100
# define KEY_A			0
# define KEY_W			13
# define KEY_D			2
# define KEY_S			1
# define KEY_ESC		53
# define KEY_L			123
# define KEY_R			124
# define ER_OPEN		0
# define ER_ARG			1
# define ER_MALLOC		2
# define ER_TEXT_PATH	3
# define ER_RES_SIZE	4
# define ER_MORE_PLAYER	5
# define ER_SCREENSHOT	6
# define ER_MAP			7
# define ER_COLOR		8

typedef struct		s_ray
{
	float			x;
	float			y;
	float			an;
	float			len;
}					t_ray;

typedef struct		s_player
{
	float			x;
	float			y;
	float			dir;
}					t_player;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_data;

typedef struct		s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct		s_sprite
{
	float			x;
	float			y;
	int				dist;
	float			dir;
	int				height;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_map
{
	int				screen_height;
	int				screen_width;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*sprite;
	int				floor_color;
	int				ceiling_color;
	int				screenshot;
	char			**map;
	char			**head_map;
}					t_map;

typedef struct		s_all
{
	t_data			*data;
	t_player		*player;
	t_texture		*text_no;
	t_texture		*text_so;
	t_texture		*text_we;
	t_texture		*text_ea;
	t_texture		*texture_sprite;
	t_sprite		*sprites;
	t_map			*map_data;
	float			dist;
}					t_all;

char				**read_map(t_list **head);
void				init_map_data(t_map *map_data);
void				free_map_data(t_map *map_data, t_list **lst, char **head);
void				free_arr(char **arr);
void				get_map_info(char **map, t_map *map_data);
void				into_struct(char *value, char *key, t_map *map_data);
void				into_struct_res(char *width, char *height, char *key,
					t_map *map_data);
void				into_struct_2(char *value, char *key, t_map *map_data);
void				valid_map(char **map);
void				check_frame(char *str, int *j);
void				valid_keys(t_map *map_data);
void				valid_path_text(t_map *map_data);
void				open_window(t_map *map_data);
void				texture_structs(t_all *all, t_map *map_data,
					t_texture *texture);
void				find_player(t_all *all, char **map);
int					press_key(int key, t_all *all);
int					display(t_all *all);
void				pixel_put(t_data *data, int x, int y, int color);
void				cast_rays(t_all *all);
float				vertic_length(t_ray *ray, t_all *all);
float				horizont_length(t_ray *ray, t_all *all);
void				printing(t_all *all, t_ray *ray, int num_ray);
void				print_3d(t_all *all, int n_ray, int text_x,
					t_texture *texture);
float				fix_ray(float ray);
void				color_screen(t_all *all);
void				find_sprites(t_all *all);
t_sprite			*new_sprite(float x, float y);
void				add_back_sprite(t_sprite **sprite, t_sprite *new);
void				sort_sprites(t_all *all);
void				swap_sprites(t_sprite **head, t_sprite *first,
					t_sprite *second);
void				print_sprites(t_all *all);
void				culc_sprite(t_all *all, t_sprite *sprite);
int					no_walls(t_all *all, t_sprite *tmp);
void				draw_sprite(t_all *all, t_point *point, float coef,
					t_sprite *sprite);
void				error(int key);
void				screenshot(t_all *all);
#endif
