.PHONY: all clean fclean re norme

SRC = mlx.c read_map.c rays.c print_3d.c error.c

NAME = cub3D

all: $(NAME)

$(NAME): $(SRC) main.c cub3d.h
	gcc main.c $(SRC) get_next_line/get_next_line.c libft/libft.a libmlx.dylib -framework OpenGL -framework Appkit -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: clean fclean all

norme:
	norminette mlx.c main.c read_map.c rays.c print_3d.c error.c