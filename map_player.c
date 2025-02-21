/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:51:57 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:04 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position(t_map *game, int i, int pos)
{
	game->player->loc_y = (double)i;
	game->player->loc_x = (double)pos;
	game->player_pos_y = i;
	game->player_pos_x = pos;
}

int	locate_player_position(t_map *game)
{
	int	count;
	int	i;
	int	pos;

	i = 0;
	count = 0;
	while (game->map_raw[i])
	{
		pos = find_character_position(game->map_raw[i], game);
		if (pos >= 0)
		{
			count++;
			set_player_position(game, i, pos);
		}
		i++;
	}
	game->map_processed[game->player_pos_y][game->player_pos_x] = '0';
	return (count != 1);
}

int	counter(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count += 1;
		i += 1;
	}
	return (count);
}
