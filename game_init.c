/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:42:18 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:29 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(&filename[len - 4], FILE_EXT, 4) == 0);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		handle_error("Invalid argument count!");
		return (1);
	}
	if (!check_file_extension(argv[1]))
	{
		handle_error("File extension must be .cub!");
		return (1);
	}
	return (0);
}

int	validate_and_load_map(t_map *game, char *file_name)
{
	read_map_characters(game, file_name);
	if (!game->map_temp)
	{
		handle_error("Cannot read the map!");
		return (1);
	}
	return (0);
}

void	setup_mlx(t_map *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		free_parser_data(game);
		handle_error("Mlx doesn't work!");
		exit(1);
	}
	game->window_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, \
						WIN_HEIGHT, "cub3D");
	if (!game->window_ptr)
	{
		free_parser_data(game);
		handle_error("Window creation failed!");
		exit(1);
	}
}

void	setup_hooks(t_map *game)
{
	mlx_hook(game->window_ptr, 2, (1L << 0), handle_key_press, game);
	mlx_hook(game->window_ptr, 3, (1L << 1), handle_key_release, game);
	mlx_hook(game->window_ptr, 17, 0, handle_game_exit, game);
	mlx_loop_hook(game->mlx_ptr, process_game_loop, game);
}
