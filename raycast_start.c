/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:52:17 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:21:56 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_player_position(t_map *game)
{
	if (game->player_direction == 'W')
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
	else if (game->player_direction == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
}

void	setup_player_variables(t_map *game)
{
	game->player->loc_x = (double)game->player_pos_x;
	game->player->loc_y = (double)game->player_pos_y;
	if (game->player_direction == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (game->player_direction == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	initialize_player_position(game);
}

void	initialize_raycast_values(t_map *game, int x)
{
	game->raycast->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	game->raycast->raydir_x = game->player->dir_x
		+ game->player->plane_x * game->raycast->camera_x;
	game->raycast->raydir_y = game->player->dir_y
		+ game->player->plane_y * game->raycast->camera_x;
	game->player_pos_x = (int)game->player->loc_x;
	game->player_pos_y = (int)game->player->loc_y;
	game->raycast->dist_x_pstep = fabs(1 / game->raycast->raydir_x);
	game->raycast->dist_y_pstep = fabs(1 / game->raycast->raydir_y);
	game->raycast->wall_hit = 0;
}
