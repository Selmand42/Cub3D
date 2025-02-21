/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:50:08 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:01:39 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_map_memory(t_map *game)
{
	int	size;

	size = game->map_height - 6 + 1;
	if (size <= 0)
		return (1);
	game->map_raw = malloc(sizeof(char *) * size);
	if (!game->map_raw)
		return (1);
	game->map_processed = malloc(sizeof(char *) * size);
	if (!game->map_processed)
	{
		free(game->map_raw);
		return (1);
	}
	game->validate_duplicates = malloc(sizeof(char *) * size);
	if (!game->validate_duplicates)
	{
		free(game->map_raw);
		free(game->map_processed);
		return (1);
	}
	return (0);
}

void	initialize_map_row(t_map *game, int j)
{
	game->map_raw[j] = NULL;
	game->map_processed[j] = NULL;
	game->validate_duplicates[j] = NULL;
}

int	is_texture_index(t_map *game, int i)
{
	return (i == game->texture_north_idx || i == game->texture_south_idx
		|| i == game->texture_east_idx || i == game->texture_west_idx
		|| i == game->texture_ceiling_idx || i == game->texture_floor_idx);
}

int	fill_map_line(t_map *game)
{
	int	i;
	int	j;

	if (allocate_map_memory(game))
		return (1);
	i = 0;
	j = 0;
	while (j <= game->initial_length - 5 && game->map_temp[i])
	{
		if (!is_texture_index(game, i))
		{
			if (game->map_temp[i] && game->map_processed
				&& game->map_raw && game->validate_duplicates)
				check_duplicate_textures(game, j++, i);
			else
				return (1);
		}
		i++;
	}
	initialize_map_row(game, j);
	return (0);
}

int	find_character_position(char *str, t_map *game)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'S' || str[i] == 'W'
			|| str[i] == 'N' || str[i] == 'E')
		{
			game->player_direction = str[i];
			return (i);
		}
		i++;
	}
	return (-1);
}
