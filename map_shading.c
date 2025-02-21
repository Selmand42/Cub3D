/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:43:47 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/19 16:01:00 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_color_data(t_map *game)
{
	char	*floor_tmp;
	char	*sky_tmp;
	char	*floor;
	char	*sky;

	floor = game->map_temp[game->texture_floor_idx];
	floor_tmp = parse_color_line(floor, game);
	if (!floor_tmp)
	{
		cleanup_game(game);
		exit (handle_error("Color error"));
	}
	game->map_temp[game->texture_floor_idx] = floor_tmp;
	sky = game->map_temp[game->texture_ceiling_idx];
	sky_tmp = parse_color_line(sky, game);
	if (!sky_tmp)
		exit (process_ceiling_texture(game));
	game->map_temp[game->texture_ceiling_idx] = sky_tmp;
	free(floor);
	free(sky);
	if (initialize_colors(game))
		exit (handle_error("Color error"));
}

char	*parse_color_line(char *line, t_map *game)
{
	char	*tmp;
	char	*tmp2;
	char	*tm;

	tm = ft_strtrim(line, "\n");
	tmp = trim_whitespace(tm);
	free(tm);
	if (!tmp)
		return (NULL);
	if (is_whitespace(tmp[1]))
	{
		tmp2 = trim_whitespace(tmp + 2);
		free(tmp);
		if (!tmp2)
		{
			handle_error("Color error");
			cleanup_game(game);
			exit (1);
		}
		tmp = tmp2;
	}
	return (tmp);
}

int	validate_rgb_values(char *a, t_map *game)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = "0123456789,";
	while (a[i])
	{
		j = 0;
		while (str[j])
		{
			if (a[i] == str[j])
				break ;
			j++;
		}
		if (!str[j])
		{
			free_color_data(game);
			handle_error("Color error");
			exit(1);
		}
		i++;
	}
	return (1);
}

int	count_color_separators(t_map *game)
{
	int	i;
	int	coma;

	i = 0;
	coma = 0;
	while (game->map_temp[game->texture_ceiling_idx][i])
		if (game->map_temp[game->texture_ceiling_idx][i++] == ',')
			coma++;
	if (coma != 2)
	{
		cleanup_game(game);
		exit (handle_error("Color coma error"));
	}
	i = 0;
	coma = 0;
	while (game->map_temp[game->texture_floor_idx][i])
		if (game->map_temp[game->texture_floor_idx][i++] == ',')
			coma++;
	if (coma != 2)
	{
		cleanup_game(game);
		exit (handle_error("Color coma error"));
	}
	return (0);
}

int	convert_color_array_to_rgb(char **color_array)
{
	int		i;
	char	*tmp;

	i = 0;
	while (color_array[i])
	{
		tmp = trim_whitespace(color_array[i]);
		if (!tmp || tmp[0] == '\n')
		{
			free(tmp);
			return (1);
		}
		free(color_array[i]);
		color_array[i] = tmp;
		i++;
	}
	if (i != 3)
	{
		return (1);
	}
	return (0);
}
