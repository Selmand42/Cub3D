/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:32:13 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:47 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_temporary_map(t_map *game)
{
	cleanup_game(game);
	handle_error("Invalid map!");
	exit(1);
}

int	validate_wall_integrity(t_map *game)
{
	return (is_valid_position(game, game->player->loc_x, game->player->loc_y));
}

int	is_valid_tile(char tile, char player_dir)
{
	return (tile == '0' || tile == '1' || tile == player_dir);
}

void	perform_map_validation(t_map *game)
{
	if (fill_map_line(game))
	{
		free_string_array(game->map_temp);
		free_game_struct(game);
		free(game);
		exit(0);
	}
	if (check_player_position(game))
		handle_map_error(game, "Invalid map, map location fail!");
	if (locate_player_position(game))
		handle_map_error(game, "Invalid map!");
}
