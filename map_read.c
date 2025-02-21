/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:46:24 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:10 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map_characters(t_map *game, char *file_name)
{
	int	fd;
	int	i;

	load_map_data(game, file_name);
	clear_map_data(game);
	if (!(game->map_temp))
	{
		game->map_temp = NULL;
		return (1);
	}
	fd = open (file_name, O_RDONLY);
	if (fd == -1)
	{
		free (game->map_temp);
		return (1);
	}
	i = 0;
	game->map_temp[i] = get_next_line(fd);
	while (game->map_temp[i++])
		game->map_temp[i] = get_next_line(fd);
	if (i < game->map_height)
		game->map_temp[i] = NULL;
	close (fd);
	return (0);
}

void	load_map_data(t_map *game, char *file_name)
{
	int		len;
	int		fd;
	char	c;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		game->map_height = 0;
		game->map_temp = NULL;
		return ;
	}
	len = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			len++;
	}
	len++;
	game->initial_length = len - 1;
	close(fd);
	game->map_temp = malloc(sizeof(char *) * (len + 1));
	if (!game->map_temp)
		return ;
	game->map_temp[len] = NULL;
	game->map_height = len;
}

void	parse_map_data(t_map *game)
{
	int	i;

	i = 0;
	initialize_texture_ids(game);
	while (game->map_temp[i])
	{
		parse_map_line(game, game->map_temp[i], i);
		i++;
	}
	if (validate_texture_ids(game))
	{
		handle_error("Missing identifier!");
		free_string_array(game->map_temp);
		free_game_struct(game);
		free(game);
		exit (0);
	}
	if (game->player_count != 1)
	{
		handle_error("Invalid player count!");
		free_string_array(game->map_temp);
		free_game_struct(game);
		free(game);
		exit (0);
	}
}

int	validate_texture_ids(t_map *game)
{
	if (game->texture_east_idx == -1 || game->texture_south_idx == -1
		|| game->texture_north_idx == -1
		|| game->texture_west_idx == -1 || game->texture_floor_idx == -1
		|| game->texture_ceiling_idx == -1)
		return (1);
	return (0);
}

void	parse_map_line(t_map *game, char	*line, int i)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
		game->texture_north_idx = i;
	else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
		game->texture_south_idx = i;
	else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
		game->texture_east_idx = i;
	else if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
		game->texture_west_idx = i;
	else if (ft_strnstr(line, "F", ft_strlen(line)) != NULL)
		game->texture_floor_idx = i;
	else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
		game->texture_ceiling_idx = i;
	else if (line && (ft_strchr(line, 'N') || ft_strchr(line, 'S')
			|| ft_strchr(line, 'E') || ft_strchr(line, 'W')))
	{
		game->player_count++;
		game->texture_player_idx = i;
	}
	else if (line
		&& (counter(line, '1') + counter(line, ' ')) == (int)ft_strlen(line) - 1
		&& game->map_start_idx == -1 && ft_strchr(line, '1'))
		game->map_start_idx = i;
}
