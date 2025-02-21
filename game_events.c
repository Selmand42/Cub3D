/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:38:44 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:22 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_game_exit(t_map *cub)
{
	free_texture_image(cub, 3);
	cleanup_mlx(cub);
	free_parser_data(cub);
	exit(0);
}

void	set_input_state(t_map *cub, int keycode, int state)
{
	if (keycode == KEY_W)
		cub->input->w = state;
	if (keycode == KEY_A)
		cub->input->a = state;
	if (keycode == KEY_S)
		cub->input->s = state;
	if (keycode == KEY_D)
		cub->input->d = state;
	if (keycode == KEY_LEFT)
		cub->input->left = state;
	if (keycode == KEY_RIGHT)
		cub->input->right = state;
}

void	update_player_state(t_map *cub)
{
	handle_movement(cub);
	handle_rotation(cub);
}

void	render_frame(t_map *cub)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_ray_position(cub, x);
		perform_dda_algorithm(cub);
		calculate_wall_properties(cub);
		draw_map_line(cub, x);
		x++;
	}
}

int	process_game_loop(void *param)
{
	t_map	*cub;

	cub = (t_map *)param;
	render_floor_ceiling(cub);
	update_player_state(cub);
	render_frame(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->window_ptr, \
							cub->image_pointer, 0, 0);
	return (0);
}
