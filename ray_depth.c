/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_depth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:53:56 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:24 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_wall_distance(t_map *game)
{
	if (game->raycast->wall_hit_dir == 0 || game->raycast->wall_hit_dir == 1)
	{
		game->raycast->perpend_dist = (game->player_pos_x - game->player->loc_x \
		+ (1 - game->raycast->step_x) / 2) / game->raycast->raydir_x;
		if (game->raycast->perpend_dist <= 0.000001)
			game->raycast->perpend_dist = 0.00001;
		return (game->player->loc_y + game->raycast->perpend_dist \
				* game->raycast->raydir_y);
	}
	game->raycast->perpend_dist = (game->player_pos_y - game->player->loc_y \
		+ (1 - game->raycast->step_y) / 2) / game->raycast->raydir_y;
	if (game->raycast->perpend_dist <= 0.000001)
		game->raycast->perpend_dist = 0.00001;
	return (game->player->loc_x + game->raycast->perpend_dist \
			* game->raycast->raydir_x);
}

void	calculate_wall_properties(t_map *game)
{
	double	wall_x;

	wall_x = calculate_wall_distance(game);
	wall_x -= floor(wall_x);
	game->raycast->height = (WIN_HEIGHT / game->raycast->perpend_dist);
	game->raycast->texture_x = (int)(wall_x * (double)TILE);
	if (game->raycast->wall_hit_dir == 0 || game->raycast->wall_hit_dir == 1)
		game->raycast->texture_x = TILE - game->raycast->texture_x - 1;
	else if (game->raycast->wall_hit_dir == 2
		|| game->raycast->wall_hit_dir == 3)
		game->raycast->texture_x = TILE - game->raycast->texture_x - 1;
	game->raycast->start_y = -game->raycast->height / 2 + WIN_HEIGHT / 2;
	if (game->raycast->start_y < 0)
		game->raycast->start_y = 0;
	game->raycast->end_y = game->raycast->height / 2 + WIN_HEIGHT / 2;
	if (game->raycast->end_y >= WIN_HEIGHT)
		game->raycast->end_y = WIN_HEIGHT - 1;
}

void	draw_map_line(t_map *game, int x)
{
	double	step;
	double	tex_pos;
	int		i;
	int		texture_y;
	int		color;

	step = 1.0 * TILE / game->raycast->height;
	tex_pos = (game->raycast->start_y - WIN_HEIGHT \
				/ 2 + game->raycast->height / 2) * step;
	i = game->raycast->start_y;
	while (i <= game->raycast->end_y)
	{
		texture_y = (int)tex_pos & 63;
		tex_pos += step;
		color = \
			game->wall_texture_array[game->raycast->wall_hit_dir] \
			->addr[(TILE * texture_y) \
			+ game->raycast->texture_x];
		game->image_buffer[i * WIN_WIDTH + x] = color;
		i++;
	}
}
