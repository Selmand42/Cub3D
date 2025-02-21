/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:58:48 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/19 22:50:22 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game_struct(t_map *game)
{
	free(game->input);
	free(game->player);
	free(game->raycast);
}

int	cleanup_game(t_map *game)
{
	free_string_array(game->map_temp);
	free_string_array(game->map_raw);
	free_string_array(game->validate_duplicates);
	free_string_array(game->map_processed);
	free_game_struct(game);
	free(game);
	return (1);
}

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_color_data(t_map *game)
{
	if (game->floor_characters)
		free_string_array(game->floor_characters);
	if (game->ceiling_characters)
		free_string_array(game->ceiling_characters);
	cleanup_game(game);
}

void	free_parser_data(t_map *game)
{
	free_string_array(game->map_temp);
	free_string_array(game->map_raw);
	free_string_array(game->map_processed);
	free_string_array(game->validate_duplicates);
	free_string_array(game->floor_characters);
	free_string_array(game->ceiling_characters);
	free(game->east_texture_path);
	free(game->south_texture_path);
	free(game->north_texture_path);
	free(game->west_texture_path);
	free(game->floor_color);
	free(game->ceiling_color);
	free_game_struct(game);
	free(game);
}
