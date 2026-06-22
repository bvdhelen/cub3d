/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 00:39:44 by ptrapero          #+#    #+#             */
/*   Updated: 2026/06/22 19:37:31 by ptrapero         ###   ########.fr       */
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

void	clean_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

float	get_distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/* Debug: Check elements and map*/
void	check_parse(t_data *data)
{
	int	i;

	i = 0;
	printf("N -> '%s'\n", data->north.path);
	printf("S -> '%s'\n", data->south.path);
	printf("E -> '%s'\n", data->east.path);
	printf("W -> '%s'\n", data->west.path);
	printf("F -> '%i' '%i' '%i'\n", data->floor_rgb[0],
		data->floor_rgb[1], data->floor_rgb[2]);
	printf("C -> '%i' '%i' '%i'\n", data->ceiling_rgb[0],
		data->ceiling_rgb[1], data->ceiling_rgb[2]);
	printf("MAP (%d x %d):\n", data->map_width, data->map_height);
	while (data->map[i])
	{
		printf("[%s]\n", data->map[i]);
		i++;
	}
}
