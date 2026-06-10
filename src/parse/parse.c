/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:53:10 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/10 21:01:06 by eldiaz-c         ###   ########.fr       */
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

static void	borrar_solo_comprueba(t_data *data)//ketchup
{
	printf("N -> '%s'\n", data->north.addr);
	printf("S -> '%s'\n", data->south.addr);
	printf("E -> '%s'\n", data->east.addr);
	printf("W -> '%s'\n", data->west.addr);
	printf("F -> '%i' '%i' '%i'\n", data->floor_rgb[0], data->floor_rgb[1], data->floor_rgb[2]);
	printf("C -> '%i' '%i' '%i'\n", data->ceiling_rgb[0], data->ceiling_rgb[1], data->ceiling_rgb[2]);
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
	borrar_solo_comprueba(data);
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
		return (-1);
	if (!map_started)
	{
		ft_lstclear(&map_lines, free);
		return (error("No map found\n"));
	}
	if (!data->floor_set || !data->ceiling_set
		|| !data->north_set || !data->south_set
		|| !data->east_set || !data->west_set)
		return (error("Mising elements\n"));
	data->floor_color = rgb_to_hex(data->floor_rgb);
	data->ceiling_color = rgb_to_hex(data->ceiling_rgb);
	result = parse_map(data, map_lines);
	ft_lstclear(&map_lines, free);
	if (result == -1)
		return (-1);
	return (0);
}
