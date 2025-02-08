/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:28:20 by selmandemir       #+#    #+#             */
/*   Updated: 2025/02/08 16:17:55 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	str_isSpace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	counter(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count += 1;
		i += 1;
	}
	return (count);
}

int	get_fd(char *path)
{
	int	fd;
	int	len;

	len = int_strlen(path);
	if (len < 5 || path[len - 1] != 'b' || path[len - 2] != 'u'
		|| path[len - 3] != 'c' || path[len - 4] != '.')
		ft_error(10);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error(9);
	return (fd);
}
