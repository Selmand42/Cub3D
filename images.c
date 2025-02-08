/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:10:56 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/08 16:06:37 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//burda free eksik
void	place_images(t_game *game, void **p, char *s)
{
	int		fd;
	int		i;
	int		j;
	char	**args;

	if (*p != 0)
		return (ft_error(11));
	args = ft_split(s, ' ');
	if (ft_split_len(args) != 2 || ft_strlen(args[0]) != 2)
		return (ft_error(11));
	fd = open(args[1], O_RDONLY, 0644);
	if (fd == -1)
		return (ft_error(12));
	*p = mlx_xpm_file_to_image(game->mlxpointer,
			args[1], &i, &j);
}

// free yok
void	place_fc(int arr[4], char *s)
{
	char	**args;
	char	**nums;

	if (arr[3] != 0)
		return (ft_error(11));
	args = ft_split(s, ' ');
	if (ft_split_len(args) != 2 || counter(args[1], ',') != 2 || ft_strlen(args[0]) != 1)
		return (ft_error(11));
	nums = ft_split(args[1], ',');
	if (ft_split_len(nums) != 3)
		return (ft_error(11));
	if (!ft_isnumeric(nums[0]) || !ft_isnumeric(nums[1]) || !ft_isnumeric(nums[2]))
		return (ft_error(11));
	if (ft_atoi(nums[0]) < 0 || ft_atoi(nums[0]) > 255 || ft_atoi(nums[1]) < 0 ||
		ft_atoi(nums[1]) > 255 || ft_atoi(nums[2]) < 0 || ft_atoi(nums[2]) > 255)
		ft_error(15);
	arr[0] = ft_atoi(nums[0]);
	arr[1] = ft_atoi(nums[1]);
	arr[2] = ft_atoi(nums[2]);
	arr[3] = 1;
}


int	exit_game(t_game *game)
{
	mlx_destroy_window(game -> mlxpointer, game -> winpointer);
	free(game -> mlxpointer);
	free(game -> line);
	exit(0);
}
/*
int	move(int direct, t_game *game)
{
	if ((game -> start) + direct < 0
		|| (game -> start) + direct >= int_strlen(game -> line))
		return (0);
	if ((game -> line)[(game -> start) + direct] != '1')
	{
		game -> start += direct;
		(game -> line)[game -> start] = 'P';
		if ((game -> start) - direct == game -> end)
			(game -> line)[(game -> start) - direct] = 'E';
		else
			(game -> line)[(game -> start) - direct] = '0';
	}
	else
		return (0);
	return (1);
}

int	keys(int command, t_game *game)
{
	if (command == 53)
		exit_game(game);
	else if (command == 0 || command == 123)
		move(-1, game);
	else if (command == 2 || command == 124)
		move(1, game);
	else if (command == 13 || command == 126)
		move(-1 * (game -> width), game);
	else if (command == 1 || command == 125)
		move(game -> width, game);
	if (game -> start == game -> end)
	{
		exit_game(game);
	}
	add_images(game);
	return (1);
}
*/
