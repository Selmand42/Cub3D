/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:52:32 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:30 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_side_distances(t_map *game)
{
	if (game->raycast->raydir_x < 0)
	{
		game->raycast->step_x = -1;
		game->raycast->next_hit_dist_x = (game->player->loc_x \
		- game->player_pos_x) * game->raycast->dist_x_pstep;
	}
	else
	{
		game->raycast->step_x = 1;
		game->raycast->next_hit_dist_x = (game->player_pos_x + 1.0 \
			- game->player->loc_x) * game->raycast->dist_x_pstep;
	}
	if (game->raycast->raydir_y < 0)
	{
		game->raycast->step_y = -1;
		game->raycast->next_hit_dist_y = (game->player->loc_y \
			- game->player_pos_y) * game->raycast->dist_y_pstep;
	}
	else
	{
		game->raycast->step_y = 1;
		game->raycast->next_hit_dist_y = (game->player_pos_y + 1.0 \
			- game->player->loc_y) * game->raycast->dist_y_pstep;
	}
}

void	calculate_ray_position(t_map *game, int x)
{
	initialize_raycast_values(game, x);
	calculate_side_distances(game);
}

void	perform_dda_algorithm(t_map *game)
{
	while (game->raycast->wall_hit == 0)
	{
		if (game->raycast->next_hit_dist_x < game->raycast->next_hit_dist_y)
		{
			game->raycast->next_hit_dist_x += game->raycast->dist_x_pstep;
			game->player_pos_x += game->raycast->step_x;
			if (game->raycast->step_x == 1)
				game->raycast->wall_hit_dir = 1;
			else
				game->raycast->wall_hit_dir = 0;
		}
		else
		{
			game->raycast->next_hit_dist_y += game->raycast->dist_y_pstep;
			game->player_pos_y += game->raycast->step_y;
			if (game->raycast->step_y == 1)
				game->raycast->wall_hit_dir = 2;
			else
				game->raycast->wall_hit_dir = 3;
		}
		if (game->map_processed[game->player_pos_y][game->player_pos_x] == '1')
			game->raycast->wall_hit = 1;
	}
}
