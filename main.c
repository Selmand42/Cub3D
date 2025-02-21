/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:41:27 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:44 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_game(t_map *game)
{
	setup_mlx(game);
	initialize_screen(game);
	setup_player_variables(game);
	initialize_wall_textures(game);
	setup_hooks(game);
	mlx_loop(game->mlx_ptr);
}

void	*allocate_component(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	cleanup_and_exit_main(t_map *game)
{
	if (game->map_temp)
		free_string_array(game->map_temp);
	if (game->input)
		free(game->input);
	if (game->player)
		free(game->player);
	if (game->raycast)
		free(game->raycast);
	if (game)
		free(game);
	exit(1);
}

void	initialize_game_state(t_map *game)
{
	game->input = allocate_component(sizeof(t_keycode));
	if (!game->input)
		cleanup_and_exit_main(game);
	game->player = allocate_component(sizeof(t_player));
	if (!game->player)
		cleanup_and_exit_main(game);
	game->raycast = allocate_component(sizeof(t_raycast));
	if (!game->raycast)
		cleanup_and_exit_main(game);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = allocate_component(sizeof(t_map));
	if (!game)
		return (1);
	if (validate_arguments(argc, argv) || validate_and_load_map(game, argv[1]))
	{
		free(game);
		return (1);
	}
	initialize_game_state(game);
	parse_map_data(game);
	perform_map_validation(game);
	validate_map_structure(game);
	process_texture_data(game);
	initialize_game(game);
	return (0);
}
