/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:39:53 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:25 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_and_exit(t_map *game, char *error_msg)
{
	free_parser_data(game);
	handle_error(error_msg);
	exit(1);
}

void	cleanup_mlx_resources(t_map *game)
{
	if (game->window_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window_ptr);
	if (game->image_pointer)
		mlx_destroy_image(game->mlx_ptr, game->image_pointer);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	free_texture_resources(t_map *game)
{
	cleanup_and_exit(game, "Malloc doesn't work!");
}

void	free_texture_image(t_map *game, int index)
{
	if (!game || !game->wall_texture_array)
		return ;
	while (index >= 0)
	{
		if (game->wall_texture_array[index])
		{
			if (game->wall_texture_array[index]->img)
				mlx_destroy_image(game->mlx_ptr,
					game->wall_texture_array[index]->img);
			free(game->wall_texture_array[index]);
		}
		index--;
	}
}

int	init_texture_struct(t_map *game, int index)
{
	game->wall_texture_array[index] = malloc(sizeof(t_textures));
	if (!game->wall_texture_array[index])
		return (0);
	return (1);
}
