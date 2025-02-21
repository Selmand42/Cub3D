NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx
FRAMES = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz 
SOURCES =  main.c map_fill.c map_validate.c map_manager.c map_start.c map_shading.c map_graphics.c map_read.c map_helpers.c \
           game_render.c game_cleanup.c game_events.c game_motion.c game_graphics.c \
           raycast_start.c raycast.c ray_depth.c map_checks.c input_handler.c texture_loader.c \
		   game_init.c parser_utils.c map_player.c

OBJS = $(SOURCES:.c=.o)

MLX = ./mlx/libmlx_Linux.a
LIBFT = ./libft/*.c
GNL = ./get_next_line/*.c

all: $(NAME)

$(NAME): $(OBJS)  $(LIBFT) $(GNL) $(MLX) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GNL) $(LIBFT) $(FRAMES) $(MLX)
	

$(OBJS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)

$(MLX):
	@$(MAKE) -C ./mlx > /dev/null 2>&1

$(LIBFT):
	@$(MAKE) -C ./libft
	
$(GNL):
	@$(MAKE) -C ./get_next_line

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./get_next_line
	@$(MAKE) clean -C ./mlx

fclean: clean
	rm -f $(NAME)
	rm -f ./libft/libft.a
	rm -f ./get_next_line/gnl.a

re:fclean all