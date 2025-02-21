/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:42:59 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:16 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_separation(t_map *game)
{
	int	player_y;
	int	player_x;

	if (!game || !game->player || !game->validate_duplicates)
		return (0);
	player_y = (int)game->player->loc_y ;
	player_x = (int)game->player->loc_x;
	if (player_y < 0 || player_y >= (int)(game->map_height - 3) ||
		player_x < 0 || player_x
		>= (int)ft_strlen(game->validate_duplicates[player_y]))
		return (0);
	return (validate_duplicates(game, player_x, player_y));
}

int	check_position_duplicate(t_map *game, int x, int y)
{
	if (!game || !game->validate_duplicates)
		return (0);
	if (y < 0 || y >= (int)(game->map_height - 6))
		return (0);
	if (!game->validate_duplicates[y])
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->validate_duplicates[y]))
		return (0);
	if (is_whitespace(game->validate_duplicates[y][x])
		|| game->validate_duplicates[y][x] == '\n')
		return (0);
	return (1);
}

int	validate_duplicates(t_map *game, int x, int y)
{
	if (!check_position_duplicate(game, x, y))
		return (1);
	if (game->validate_duplicates[y][x] == 'X')
		return (1);
	game->validate_duplicates[y][x] = 'X';
	if (check_position_duplicate(game, x + 1, y))
		validate_duplicates(game, x + 1, y);
	if (check_position_duplicate(game, x - 1, y))
		validate_duplicates(game, x - 1, y);
	if (check_position_duplicate(game, x, y + 1))
		validate_duplicates(game, x, y + 1);
	if (check_position_duplicate(game, x, y - 1))
		validate_duplicates(game, x, y - 1);
	return (1);
}

void	validate_map_width(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->validate_duplicates[i])
	{
		j = 0;
		while (game->validate_duplicates[i][j])
		{
			if (game->validate_duplicates[i][j] != 'X'
				&& game->validate_duplicates[i][j] != '\n' &&
				!is_whitespace(game->validate_duplicates[i][j]))
			{
				handle_error("Island on the map file!");
				cleanup_game(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	validate_map_structure(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	validate_map_characters(game);
	while (game->map_raw[i])
	{
		j = 0;
		while (game->map_raw[i][j])
		{
			if (validate_map_section (i, j, game))
			{
				handle_error("Map is not valid");
				cleanup_game(game);
				exit (1);
			}
			j++;
		}
		i++;
	}
	check_map_separation(game);
	validate_map_width(game);
	validate_wall_integrity(game);
	process_color_data(game);
}
