/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:45:37 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:21:38 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initialize_colors(t_map	*game)
{
	if (count_color_separators(game))
		return (1);
	game->floor_characters = ft_split(game->map_temp[game->texture_floor_idx], \
							',');
	if (!game->floor_characters)
		return (1);
	game->ceiling_characters = ft_split \
							(game->map_temp[game->texture_ceiling_idx], ',');
	if (!game->ceiling_characters)
	{
		free_string_array(game->floor_characters);
		return (1);
	}
	if (convert_color_array_to_rgb(game->floor_characters) || \
		convert_color_array_to_rgb(game->ceiling_characters))
	{
		free_string_array(game->floor_characters);
		free_string_array(game->ceiling_characters);
		return (1);
	}
	parse_color_values(game);
	return (0);
}

void	cleanup_color_allocation(t_map *game, int is_floor)
{
	if (is_floor)
	{
		free_color_data(game);
	}
	else
	{
		free(game->floor_color);
		free_color_data(game);
	}
	cleanup_game(game);
	handle_error("Memory allocation failed!");
	exit(1);
}

int	*create_color_array(t_map *game, int is_floor)
{
	int	*array;

	array = (int *)malloc(3 * sizeof(int));
	if (!array)
		cleanup_color_allocation(game, is_floor);
	return (array);
}

int	validate_color_component(int value)
{
	return (value >= 0 && value <= 255);
}

void	convert_color_values(t_map *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		game->ceiling_color[i] = ft_atoi(game->ceiling_characters[i]);
		game->floor_color[i] = ft_atoi(game->floor_characters[i]);
		i++;
	}
}
