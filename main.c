/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 05:13:21 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/08 16:05:16 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error(int num)
{
	ft_printf("Error\n");
	if (num == 0)
		ft_printf("I just want one map!\n");
	else if (num == 1)
		ft_printf("Length of the walls are not good.\n");
	else if (num == 2)
		ft_printf("There is a gap between walls.\n");
	else if (num == 3)
		ft_printf("There is not enough coin.\n");
	else if (num == 4)
		ft_printf("The map contaion just and exactly one exit!\n");
	else if (num == 5)
		ft_printf("Where is the start position!\n");
	else if (num == 6)
		ft_printf("Why there is foreign things???\n");
	else if (num == 9)
		ft_printf("There is not a map like that!\n");
	else if (num == 10)
		ft_printf("The extension of file is not .cub!\n");
	else if (num == 11)
		ft_printf("Uygun bir harita gir lutfen\n");
	else if (num == 12)
		ft_printf("Uygun bir resim gir lutfen\n");
	else if (num == 13)
		ft_printf("Mallocn't\n");
	else if (num == 14)
		ft_printf("Haritada erisilemeyen alan var!\n");
	else if (num == 15)
		ft_printf("Baf RGB values!\n");
	else if (num == 16)
		ft_printf("Please close the map!\n");
	exit(0);
}

int	map(t_game *game, char *arg)
{
	game -> NO = 0;
	game -> SO = 0;
	game -> EA = 0;
	game -> WE = 0;

	read_map(game, arg);
	check_data(game);
	if (game->NO == 0 || game->SO == 0 || game->WE == 0 || game->EA == 0)
		ft_error(12);
	if (game->F[3] == 0 || game->C[3] == 0)
		ft_error(12);
	check_and_get_sth(game);
	check_borders(game);
	return (1);
}
/*
int	play(t_game *game)
{
	int	i;
	int camera_x;

	game -> plane_x = 0;
	game -> plane_y = 0.66;
	game -> player_dx = (1 - game -> player_d) * (1 - abs(game -> player_d - 2)) + (game -> player_d - 1)* (game -> player_d - 3);
	game -> player_dy = (game -> player_d - 1) * (game -> player_d - 3) - (game -> player_d - 1) * (game -> player_d - 2);
	i = 0;
	while (i < 1200) {
		camera_x = 2 * i / 1200 - 1;
		//double rayplayer_dx = game -> player_dx + game -> plane_x * camera_x;
		//double rayplayer_dy = game -> player_dy + game -> plane_y * camera_x;

	}
	return (0);
}
*/


int	main(int arg, char **argv)
{
	t_game	*game;
	game = malloc(sizeof(t_game));
	if (arg != 2)
		ft_error(0);
	game -> mlxpointer = mlx_init();
	map(game, argv[1]);
	game -> winpointer = mlx_new_window(game -> mlxpointer,
			(1200), (1000), "cub3D");

	//draw_scene(game);
//	place_images(game);
	//mlx_key_hook(game -> winpointer, keys, game);
	mlx_hook(game -> winpointer, 17, 0, (void *)exit, 0);
	mlx_loop(game -> mlxpointer);
	return (0);
}
