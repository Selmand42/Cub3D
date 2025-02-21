/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:19 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:00 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_forbidden_character(char c)
{
	return (!is_valid_map_char(c));
}

int	check_adjacent_tiles(t_map *game, int i, int j)
{
	if (i == 0 || !game->map_raw[i - 1] || \
		is_forbidden_character(game->map_raw[i - 1][j]))
		return (1);
	if (!game->map_raw[i + 1] || \
		is_forbidden_character(game->map_raw[i + 1][j]))
		return (1);
	if (j == 0 || is_forbidden_character(game->map_raw[i][j - 1]))
		return (1);
	if (!game->map_raw[i][j + 1] || \
		is_forbidden_character(game->map_raw[i][j + 1]))
		return (1);
	return (0);
}

int	validate_map_section(int i, int j, t_map *game)
{
	if (game->map_raw[i][j] == '0')
		return (check_adjacent_tiles(game, i, j));
	return (0);
}

void	handle_invalid_map(t_map *game)
{
	cleanup_game(game);
	exit(handle_error("Invalid object on the map file!"));
}

void	validate_map_characters(t_map *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->map_raw[i])
	{
		j = 0;
		while (game->map_raw[i][j])
		{
			if (game->player_direction == game->map_raw[i][j])
				player_count++;
			if (is_forbidden_character(game->map_raw[i][j]) &&
				is_special_char(game->map_raw[i][j]))
				handle_invalid_map(game);
			j++;
		}
		i++;
	}
	validate_player_count(game, player_count);
}
