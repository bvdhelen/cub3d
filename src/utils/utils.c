/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 00:39:44 by ptrapero          #+#    #+#             */
/*   Updated: 2026/06/19 22:06:15 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	charnull_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	s[i] = '\0';
}

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

int	rgb_to_hex(int *rgb)
{
	int	hex;

	hex = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (hex);
}

float	get_distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}
