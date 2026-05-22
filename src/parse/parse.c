/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:53:10 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/22 12:16:12 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '1' || line[i] == '0');
}

static void	clean_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

/*
 * Función que decide qué hacer con cada línea:
 * si es inicio de mapa devuelve 1 (para añadir a lista)
 * si es elemento lo procesa
 * si no es nada devuelve 0 (se descarta)
 * si hay error, -1
*/

static int	process_line(char *line, t_data *data, int *map_started)
{
	if (!*map_started)
	{
		if (is_map_line(line))
		{
			*map_started = 1;
			return (1);
		}
		else if (parse_elements(line, data) == -1)
			return (-1);
		else
			return (0);
	}
	return (1);
}

static int	read_lines(int fd, t_data *data, t_list **map_lines,
		int *map_started)
{
	char	*file;
	int		ret;

	file = get_next_line(fd);
	while (file)
	{
		charnull_gnl(file);
		//ketchup revisar no se rompe la parte de elena,
			//si no call desde parse_elements
		ret = process_line(file, data, map_started);
		if (ret == -1)
		{
			free(file);
			clean_gnl(fd);
			return (-1);
		}
		if (ret == 1)
			ft_lstadd_back(map_lines, ft_lstnew(file));
		else
			free(file);
		file = get_next_line(fd);
	}
	return (0);
}

int	parse_file(int fd, t_data *data)
{
	int		map_started;
	t_list	*map_lines;
	int		result;

	map_started = 0;
	map_lines = NULL;
	if (read_lines(fd, data, &map_lines, &map_started) == -1)
		return (error("Invalid element\n"));
	if (!map_started)
	{
		ft_lstclear(&map_lines, free);
		return (error("No map found\n"));
	}
	if (!data->floor_set || !data->ceiling_set
		|| !data->north_set || !data->south_set
		|| !data->east_set || !data->west_set)
		return (error("Mising elements\n"));//ketchup
	result = parse_map(data, map_lines);
	ft_lstclear(&map_lines, free);
	if (result == -1)
		return (-1);
	return (0);
}
