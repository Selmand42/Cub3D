/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:36:49 by muhademi          #+#    #+#             */
/*   Updated: 2025/02/17 20:36:54 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	memnbr;

	memnbr = count * size;
	str = (void *)malloc(memnbr);
	if (!str)
	{
		return (0);
	}
	ft_bzero(str, memnbr);
	return (str);
}
