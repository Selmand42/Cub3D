/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:34:07 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 13:32:34 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_screen(t_map *game)
{
	game->image_pointer = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->image_pointer)
		cleanup_and_exit(game, "image_pointer error!");
	game->image_buffer = (int *)mlx_get_data_addr(game->image_pointer,
			&game->bits_per_pixel, &game->line_length, &game->endian);
	if (!game->image_buffer)
		cleanup_and_exit(game, "image_buffer error!");
	initialize_textures(game);
}

void	initialize_textures(t_map *game)
{
	game->ceiling_tex_enabled = (game->ceiling_color[0] << 16) \
	| (game->ceiling_color[1] << 8) | game->ceiling_color[2];
	game->floor_tex_enabled = (game->floor_color[0] << 16) \
	| (game->floor_color[1] << 8) | game->floor_color[2];
}

void	render_floor_ceiling(t_map *game)
{
	int	half_height;
	int	row_size;
	int	i;

	i = 0;
	half_height = WIN_HEIGHT / 2;
	row_size = WIN_WIDTH * sizeof(int);
	while (i < half_height)
	{	
		ft_memset(&game->image_buffer[i * WIN_WIDTH], \
		game->ceiling_tex_enabled, row_size);
		i++;
	}
	i = half_height;
	while (i < WIN_HEIGHT)
	{
		ft_memset(&game->image_buffer[i * WIN_WIDTH], \
		game->floor_tex_enabled, row_size);
		i++;
	}
}

void	initialize_texture_ids(t_map *game)
{
	game->texture_east_idx = -1;
	game->texture_south_idx = -1;
	game->texture_north_idx = -1;
	game->texture_west_idx = -1;
	game->texture_floor_idx = -1;
	game->texture_ceiling_idx = -1;
	game->player_count = 0;
	game->map_start_idx = -1;
}

void	check_duplicate_textures(t_map *game, int j, int i)
{
	char	*source;

	source = game->map_temp[i];
	game->map_processed[j] = ft_strdup(source);
	game->map_raw[j] = ft_strdup(source);
	game->validate_duplicates[j] = ft_strdup(source);
}
