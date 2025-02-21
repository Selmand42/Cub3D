/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:18:07 by usisman           #+#    #+#             */
/*   Updated: 2025/02/18 13:32:48 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surrounding_tiles(t_map *game, int x, int y)
{
	char	**map;
	char	player_dir;

	map = game->map_raw;
	player_dir = game->player_direction;
	if (!is_valid_tile(map[y][x + 1], player_dir) || \
		!is_valid_tile(map[y][x - 1], player_dir) || \
		!is_valid_tile(map[y + 1][x], player_dir) || \
		!is_valid_tile(map[y - 1][x], player_dir))
		return (0);
	return (1);
}

void	flood_fill_tile(t_map *game, int x, int y)
{
	if (game->map_raw[y][x] == '0')
	{
		game->map_raw[y][x] = game->player_direction;
		is_valid_position(game, x, y);
	}
}

int	is_valid_position(t_map *game, int x, int y)
{
	if (!check_surrounding_tiles(game, x, y))
		free_temporary_map(game);
	flood_fill_tile(game, x + 1, y);
	flood_fill_tile(game, x - 1, y);
	flood_fill_tile(game, x, y + 1);
	flood_fill_tile(game, x, y - 1);
	return (1);
}

int	check_player_position(t_map *game)
{
	return (game->texture_player_idx < game->texture_north_idx || \
			game->texture_player_idx < game->texture_south_idx || \
			game->texture_player_idx < game->texture_east_idx || \
			game->texture_player_idx < game->texture_west_idx || \
			game->texture_player_idx < game->texture_floor_idx || \
			game->texture_player_idx < game->texture_ceiling_idx || \
			game->map_start_idx < game->texture_north_idx || \
			game->map_start_idx < game->texture_south_idx || \
			game->map_start_idx < game->texture_east_idx || \
			game->map_start_idx < game->texture_west_idx || \
			game->map_start_idx < game->texture_floor_idx || \
			game->map_start_idx < game->texture_ceiling_idx);
}

void	handle_map_error(t_map *game, char *error_msg)
{
	cleanup_game(game);
	handle_error(error_msg);
	exit(1);
}
