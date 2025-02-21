/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:39:12 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/20 15:51:51 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_map *game, int direction)
{
	double	des_x;
	double	des_y;

	des_x = game->player->loc_x + game->player->dir_x * (double)1 / 60
		* direction;
	des_y = game->player->loc_y + game->player->dir_y * (double)1 / 60
		* direction;
	if (game->map_processed[(int)game->player->loc_y][(int)des_x] == '0')
		game->player->loc_x = des_x;
	if (game->map_processed[(int)des_y][(int)game->player->loc_x] == '0')
		game->player->loc_y = des_y;
}

void	move_left_right(t_map *game, int direction)
{
	double	des_x;
	double	des_y;

	des_x = game->player->loc_x + game->player->plane_x
		* (double)1 / 50 * direction;
	des_y = game->player->loc_y + game->player->plane_y
		* (double)1 / 50 * direction;
	if (game->map_processed[(int)game->player->loc_y][(int)des_x] == '0')
		game->player->loc_x = des_x;
	if (game->map_processed[(int)des_y][(int)game->player->loc_x] == '0')
		game->player->loc_y = des_y;
}

void	rotate_camera(t_map *game, int direction)
{
	double	old_dirx;
	double	old_planex;
	double	rotate_angle;

	rotate_angle = 0.01 * direction;
	old_dirx = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rotate_angle)
		- game->player->dir_y * sin(rotate_angle);
	game->player->dir_y = old_dirx * sin(rotate_angle)
		+ game->player->dir_y * cos(rotate_angle);
	old_planex = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rotate_angle)
		- game->player->plane_y * sin(rotate_angle);
	game->player->plane_y = old_planex * sin(rotate_angle)
		+ game->player->plane_y * cos(rotate_angle);
}

int	is_special_char(int input)
{
	return (input > 32 && input <= 126);
}

void	validate_player_count(t_map *game, int count)
{
	if (count != 1)
	{
		cleanup_game(game);
		handle_error("Invalid character count on the map file!");
		exit(1);
	}
}
