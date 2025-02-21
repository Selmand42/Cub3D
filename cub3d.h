/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:57:57 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/18 14:23:56 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define FILE_EXT ".cub"
# define WIN_HEIGHT 750
# define WIN_WIDTH 1200
# define TILE 64

typedef struct s_keycode
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keycode;

typedef struct s_player
{
	double		loc_x;
	double		loc_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_raycast
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	double		next_hit_dist_x;
	double		next_hit_dist_y;
	double		dist_x_pstep;
	double		dist_y_pstep;
	int			step_x;
	int			step_y;
	int			wall_hit_dir;
	int			wall_hit;

	int			texture_x;
	int			texture_y;

	double		perpend_dist;
	int			height;
	int			start_y;
	int			end_y;
}				t_raycast;

typedef struct s_textures
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_textures;

typedef struct s_map
{
	int			texture_east_idx;
	int			texture_north_idx;
	int			texture_south_idx;
	int			texture_west_idx;
	int			texture_ceiling_idx;
	int			texture_floor_idx;
	int			map_start_idx;
	int			texture_player_idx;
	int			initial_length;
	char		**ceiling_characters;
	char		**floor_characters;
	char		*east_texture_path;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	int			*floor_color;
	int			*ceiling_color;
	char		**map_raw;
	char		**map_processed;
	char		**map_temp;
	char		**validate_duplicates;
	int			map_width;
	int			map_height;
	char		*file_name;

	t_keycode	*input;
	t_player	*player;
	t_raycast	*raycast;
	t_textures	*wall_texture_array[4];

	void		*mlx_ptr;
	void		*window_ptr;

	int			floor_tex_enabled;
	int			ceiling_tex_enabled;

	void		*image_pointer;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			*image_buffer;

	int			player_count;
	char		player_direction;
	int			player_pos_x;
	int			player_pos_y;
	int			current_row;
	int			current_col;

}				t_map;

void		initialize_textures(t_map *game);
void		render_floor_ceiling(t_map *game);
void		initialize_screen(t_map *game);
void		initialize_texture_ids(t_map *game);
void		check_duplicate_textures(t_map *game, int j, int i);
void		free_game_struct(t_map *game);
int			cleanup_game(t_map *game);
void		free_string_array(char **arr);
void		free_color_data(t_map *game);
void		free_parser_data(t_map *game);
int			handle_game_exit(t_map *game);
int			handle_key_press(int keycode, t_map *game);
int			handle_key_release(int keycode, t_map *game);
void		update_player_state(t_map *game);
int			process_game_loop(void *param);
void		move_forward_backward(t_map *game, int direction);
void		move_left_right(t_map *game, int direction);
void		rotate_camera(t_map *game, int direction);
int			is_special_char(int input);
void		validate_player_count(t_map *game, int count);
void		free_texture_resources(t_map *game);
void		load_texture_from_xpm(t_map *game, char *path, int index);
void		initialize_wall_textures(t_map *game);
void		handle_texture_error(t_map *game, int index);
void		free_texture_image(t_map *game, int index);
int			validate_arguments(int argc, char **argv);
int			validate_and_load_map(t_map *game, char *file_name);
void		initialize_game(t_map *game);
void		initialize_game_state(t_map *game);
int			check_map_separation(t_map *game);
int			check_position_duplicate(t_map *game, int x, int y);
int			validate_duplicates(t_map *game, int x, int y);
void		validate_map_width(t_map *game);
void		validate_map_structure(t_map *game);
void		process_color_data(t_map *game);
char		*parse_color_line(char *line, t_map *game);
int			validate_rgb_values(char *a, t_map *game);
int			count_color_separators(t_map *game);
int			convert_color_array_to_rgb(char **color_array);
int			is_whitespace(char c);
char		*trim_whitespace(char *s);
int			is_forbidden_character(char c);
int			validate_map_section(int i, int j, t_map *game);
void		validate_map_characters(t_map *game);
void		free_temporary_map(t_map *game);
int			validate_wall_integrity(t_map *game);
int			is_valid_position(t_map *game, int x, int y);
int			check_surrounding_tiles(t_map *game, int x, int y);
void		perform_map_validation(t_map *game);
int			initialize_colors(t_map	*game);
int			*create_color_array(t_map *game, int is_floor);
void		convert_color_values(t_map *game);
void		parse_color_values(t_map *game);
int			validate_color_range(t_map *game);
int			read_map_characters(t_map *game, char *file_name);
void		load_map_data(t_map *game, char *file_name);
void		parse_map_data(t_map *game);
int			validate_texture_ids(t_map *game);
void		parse_map_line(t_map *game, char	*line, int i);
char		*parse_texture_path(char *line, t_map *game);
void		process_texture_data(t_map *game);
void		clear_map_data(t_map *game);
int			handle_error(char *line);
int			process_ceiling_texture(t_map *game);
int			allocate_map_memory(t_map *game);
void		initialize_map_row(t_map *game, int j);
int			fill_map_line(t_map *game);
int			find_character_position(char *str, t_map *game);
int			locate_player_position(t_map *game);
void		initialize_player_position(t_map *game);
void		setup_player_variables(t_map *game);
void		initialize_raycast_values(t_map *game, int x);
void		calculate_side_distances(t_map *game);
void		calculate_ray_position(t_map *game, int x);
void		perform_dda_algorithm(t_map *game);
double		calculate_wall_distance(t_map *game);
void		calculate_wall_properties(t_map *game);
void		draw_map_line(t_map *game, int x);
void		cleanup_mlx(t_map *cub);
void		handle_rotation(t_map *cub);
void		handle_movement(t_map *cub);
int			handle_key_release(int keycode, t_map *cub);
int			handle_key_press(int keycode, t_map *cub);
void		free_temporary_map(t_map *game);
int			validate_wall_integrity(t_map *game);
int			is_valid_tile(char tile, char player_dir);
void		perform_map_validation(t_map *game);
void		cleanup_and_exit(t_map *game, char *error_msg);
void		handle_texture_error(t_map *game, int index);
void		initialize_wall_textures(t_map *game);
void		load_texture_from_xpm(t_map *game, char *path, int index);
int			get_texture_data(t_map *game, int index);
int			load_texture_image(t_map *game, char *path, int index);
void		setup_hooks(t_map *game);
void		setup_mlx(t_map *game);
int			validate_and_load_map(t_map *game, char *file_name);
int			validate_arguments(int argc, char **argv);
int			check_file_extension(const char *filename);
int			is_valid_map_char(char c);
char		*trim_whitespace(char *s);
int			is_whitespace(char c);
void		parse_color_values(t_map *game);
int			validate_color_range(t_map *game);
void		set_player_position(t_map *game, int i, int pos);
int			locate_player_position(t_map *game);
void		set_input_state(t_map *cub, int keycode, int state);
int			validate_color_component(int value);
void		cleanup_mlx_resources(t_map *game);
void		free_texture_image(t_map *game, int index);
int			check_player_position(t_map *game);
void		handle_map_error(t_map *game, char *error_msg);
int			init_texture_struct(t_map *game, int index);
int			counter(char *line, char c);

#endif
