/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:37:25 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:41 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int keycode, t_map *cub)
{
	if (keycode == KEY_ESC)
		handle_game_exit(cub);
	set_input_state(cub, keycode, 1);
	return (0);
}

int	handle_key_release(int keycode, t_map *cub)
{
	set_input_state(cub, keycode, 0);
	return (0);
}

void	handle_movement(t_map *cub)
{
	if (cub->input->w)
		move_forward_backward(cub, 1);
	else if (cub->input->s)
		move_forward_backward(cub, -1);
	if (cub->input->d)
		move_left_right(cub, 1);
	else if (cub->input->a)
		move_left_right(cub, -1);
}

void	handle_rotation(t_map *cub)
{
	if (cub->input->right)
		rotate_camera(cub, 1);
	else if (cub->input->left)
		rotate_camera(cub, -1);
}

void	cleanup_mlx(t_map *cub)
{
	if (cub->window_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->window_ptr);
	if (cub->image_pointer)
		mlx_destroy_image(cub->mlx_ptr, cub->image_pointer);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
}
