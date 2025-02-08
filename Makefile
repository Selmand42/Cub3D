NAME := cub3D

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := main.c map.c images.c utils.c
PRINTF := lib/ft_printf/*c
GETNEXTLINE := lib/get_next_line/*c
LIBFT := lib/libft/*c
LIBRARY := -Lminilibx -lmlx -framework OpenGL -framework AppKit
MINILIBX := minilibx/


all:
	@make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(GETNEXTLINE) $(PRINTF) $(LIBFT) $(LIBRARY) -o $(NAME)

clean:


fclean: clean
		@make clean -C $(MINILIBX)
		rm -rf $(NAME)


re: fclean all
