/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:34:32 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/08 16:05:30 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Cub3D
# define Cub3D

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "lib/get_next_line/get_next_line.h"
# include "lib/ft_printf/ft_printf.h"
# include "lib/libft/libft.h"
# include "minilibx/mlx.h"


typedef struct s_game
{
	char	*line;
	char	**map;
	void	*floor;
	void	*barrier;
	void	*player;

	void	*mlxpointer;
	void	*winpointer;

	int		map_start;
	int		player_x;
	int		player_y;
	int		player_d;

	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	int		F[4];
	int		C[4];

	float	plane_x;
	float	plane_y;
	float	player_dx;
	float	player_dy;
	int		SCREEN_HEIGHT;
	int		SCREEN_WIDTH;
}	t_game;

void	ft_error(int num);
int		map(t_game *game, char *arg);
void	check_data(t_game *game);
void	check_and_get_sth(t_game *game);
int		counter(char *str, char c);
int		read_map(t_game *game, char *path);
void	place_images(t_game *game, void **p, char *s);
int		exit_game(t_game *game);
int		get_fd(char *path);

void	place_fc(int arr[4], char *s);
int		isWhiteSpace(int c);
int		str_isWhiteSpace(char *s);
int		dfs(t_game *game, int x, int y, char **visited);
char	**copy_map(t_game *game);
void	check_borders(t_game *game);

#endif
