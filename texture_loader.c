/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:41:00 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:33:33 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture_image(t_map *game, char *path, int index)
{
	game->wall_texture_array[index]->img = mlx_xpm_file_to_image(game->mlx_ptr, \
										path, \
										&game->wall_texture_array[index]->w, \
										&game->wall_texture_array[index]->h);
	if (!game->wall_texture_array[index]->img)
		return (0);
	return (1);
}

int	get_texture_data(t_map *game, int index)
{
	game->wall_texture_array[index]->addr = (int *)mlx_get_data_addr(\
		game->wall_texture_array[index]->img, \
		&game->wall_texture_array[index]->bpp, \
		&game->wall_texture_array[index]->line_len, \
		&game->wall_texture_array[index]->endian);
	if (!game->wall_texture_array[index]->addr)
		return (0);
	return (1);
}

void	load_texture_from_xpm(t_map *game, char *path, int index)
{
	if (!init_texture_struct(game, index))
		cleanup_and_exit(game, "Malloc doesn't work!");
	if (!load_texture_image(game, path, index))
	{
		handle_texture_error(game, index);
		exit(1);
	}
	if (!get_texture_data(game, index))
	{
		handle_texture_error(game, index);
		exit(1);
	}
}

void	initialize_wall_textures(t_map *game)
{
	load_texture_from_xpm(game, game->east_texture_path, 0);
	load_texture_from_xpm(game, game->west_texture_path, 1);
	load_texture_from_xpm(game, game->north_texture_path, 2);
	load_texture_from_xpm(game, game->south_texture_path, 3);
}

void	handle_texture_error(t_map *game, int index)
{
	free_texture_image(game, index);
	cleanup_mlx_resources(game);
	cleanup_and_exit(game, "Image doesn't work!");
}
