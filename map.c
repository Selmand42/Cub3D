/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 05:49:46 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/08 16:05:09 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int	read_map(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = get_fd(path);
	line = get_next_line(fd);
	game -> line = 0;
	while (line)
	{
		game -> line = join(game -> line, line);
		if (game -> line && game -> line [int_strlen(game -> line ) - 1] != '\n')
			game -> line  = join(game -> line , "\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game -> map = ft_split(game -> line, '\n');
	return (0);
}

void	check_data(t_game *game)
{
	int	i;

	i = 0;

	game ->map_start = -1;
	(game -> F)[3] = 0;
	(game -> C)[3] = 0;
	while (game -> map[i])
	{
		if (ft_strnstr(game ->map[i], "NO ", 3))
			place_images(game, &(game -> NO), game -> map[i]);
		else if (ft_strnstr(game ->map[i], "SO ", 3))
			place_images(game, &(game -> SO), game -> map[i]);
		else if (ft_strnstr(game ->map[i], "WE ", 3))
			place_images(game, &(game -> WE), game -> map[i]);
		else if (ft_strnstr((game ->map[i]), "EA ", 3))
			place_images(game, &(game -> EA), game -> map[i]);
		else if (ft_strnstr(game ->map[i], "F ", 2))
			place_fc(game -> F, game -> map[i]);
		else if (ft_strnstr(game ->map[i], "C ", 2))
			place_fc(game->C, game -> map[i]);
		else if (!str_isWhiteSpace(game ->map[i]) && game -> map_start == -1)
			game -> map_start = i;
		i++;
	}
}

void	check_and_get_sth(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = game -> map_start;
	if (i == -1)
		return (ft_error(11));

	while (game -> map[i])
	{
		j = 0;
		while (game -> map[i][j])
		{
			if (game ->map[i][j] == 'N' || game ->map[i][j] == 'W' || game ->map[i][j] == 'E' || game ->map[i][j] == 'S')
			{
				game ->	player_x = i;
				game -> player_y = j;
				game -> player_d = ((game -> map[i][j]) - 69) / 6;
				count += 1;
			}
			else if (game ->map[i][j] != '1' && game ->map[i][j] != '0' && !isWhiteSpace(game -> map[i][j]))
				ft_error(12);
			j += 1;
		}
		i++;
	}
	if (count != 1)
		ft_error(11);
}

void	check_borders(t_game *game)
{
	char **temp;

	temp = copy_map(game);
	temp[game -> player_x - game -> map_start][game -> player_y] = '0';
	int i = dfs(game, game -> player_x - game -> map_start, game -> player_y, temp);
	if (i)
		ft_error(16);
}

int	dfs(t_game *game, int x, int y, char **visited)
{
	if (x < 0  || x >= ft_split_len(visited)
		|| y < 0 || y >= int_strlen(visited[x]) ||
		(visited[x][y] != '1' && visited[x][y] != '0'))
		return (1);
	if (visited[x][y] == '1')
		return (0);
	visited[x][y] = '1';
	return (dfs(game, x + 1, y, visited)
		+ dfs(game, x - 1, y, visited)
		+ dfs(game, x, y + 1, visited)
		+ dfs(game, x, y - 1, visited));
}

char	**copy_map(t_game *game)
{
	int	i;
	char **new;

	new = malloc(sizeof(char *) * (ft_split_len(game -> map) - game -> map_start + 1));
	if (!new)
		ft_error(13);
	i = game -> map_start;
	while (game -> map[i])
	{
		new[i - game -> map_start] = ft_strdup(game -> map[i]);
		i++;
	}
	new[i - game -> map_start] = 0;
	return new;
}
