.PHONY: all clean fclean re norme

NAME = cub3D

SRC = main.c read_map.c valid.c mlx.c rays.c print_3d.c find_sprites.c print_sprites.c error.c screenshot.c get_next_line/get_next_line.c

SRCO = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

MLX = libmlx.dylib

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) $(MLX)  cub3d.h
	@gcc libft/libft.a libmlx.dylib -framework OpenGL -framework Appkit $(SRCO) -o $(NAME)

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

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib
	@rm -f ./mlx/libmlx.dylib
	@make clean -C ./libft/

re: fclean all

norme:
	@norminette $(SRC)