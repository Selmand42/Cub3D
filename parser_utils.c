/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:59 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:12:22 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

char	*trim_whitespace(char *s)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && is_whitespace(s[start]))
		start++;
	end = ft_strlen(s);
	while (end > start && is_whitespace(s[end - 1]))
		end--;
	len = end - start;
	return (ft_substr(s, start, len));
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'W' || \
			c == 'S' || c == 'E');
}

void	parse_color_values(t_map *game)
{
	int	i;

	i = 0;
	while (game->ceiling_characters[i])
		validate_rgb_values(game->ceiling_characters[i++], game);
	i = 0;
	while (game->floor_characters[i])
		validate_rgb_values(game->floor_characters[i++], game);
	game->floor_color = create_color_array(game, 1);
	game->ceiling_color = create_color_array(game, 0);
	convert_color_values(game);
	if (validate_color_range(game))
	{
		free(game->floor_color);
		free(game->ceiling_color);
		free_color_data(game);
		handle_error("Invalid color range!");
		exit(1);
	}
}

int	validate_color_range(t_map *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!validate_color_component(game->ceiling_color[i]) || \
			!validate_color_component(game->floor_color[i]))
			return (1);
		i++;
	}
	return (0);
}
