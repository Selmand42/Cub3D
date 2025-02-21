/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:47:41 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:17:28 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*parse_texture_path(char *line, t_map *game)
{
	char	*tmp;
	char	*path;
	char	*sp;

	sp = trim_whitespace(line);
	if (!is_whitespace(sp[2]))
	{	
		handle_error("Texture doesn't work!");
		free_string_array(game->floor_characters);
		free_string_array(game->ceiling_characters);
		free(game->floor_color);
		free(game->ceiling_color);
		cleanup_game(game);
		free(sp);
		exit(1);
	}
	tmp = ft_strtrim(sp, "\n");
	path = trim_whitespace(tmp + 2);
	free (tmp);
	free (sp);
	return (path);
}

void	process_texture_data(t_map *game)
{
	game->east_texture_path = parse_texture_path
		(game->map_temp[game->texture_east_idx], game);
	game->north_texture_path = parse_texture_path
		(game->map_temp[game->texture_north_idx], game);
	game->south_texture_path = parse_texture_path
		(game->map_temp[game->texture_south_idx], game);
	game->west_texture_path = parse_texture_path
		(game->map_temp[game->texture_west_idx], game);
}

void	clear_map_data(t_map *game)
{
	if (game->map_height == 1)
	{
		free_string_array(game->map_temp);
		free(game);
		handle_error("Empty map or invalid map!");
		exit (0);
	}
}

int	handle_error(char *line)
{
	printf("Error\n%s\n", line);
	return (1);
}

int	process_ceiling_texture(t_map *game)
{
	free_string_array(game->floor_characters);
	cleanup_game(game);
	handle_error("Color error");
	return (1);
}
