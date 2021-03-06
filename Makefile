.PHONY: all clean fclean re norme

NAME = cub3D

SRC = main.c get_map_info.c close_window.c valid.c open_window.c move.c arrays.c find_player.c pixel_put.c rays.c print_3d.c find_sprites.c print_sprites.c error.c screenshot.c get_next_line/get_next_line.c

SRCO = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

MLX = libmlx.dylib

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) $(MLX)  cub3d.h
	@gcc -g libft/libft.a libmlx.dylib -framework OpenGL -framework Appkit $(SRCO) -o $(NAME)

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./mlx
	@cp mlx/libmlx.dylib ./

%.o:%.c cub3d.h
	@gcc $(FLAGS) -I mlx -c $< -o $@

clean:
	@rm -f $(SRCO)
	@make clean -C ./libft/
	@make clean -C ./mlx/

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib
	@rm -f ./mlx/libmlx.dylib

re: fclean all

norme:
	@norminette $(SRC) cub3d.h ./libft/*.c