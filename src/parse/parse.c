/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:53:10 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/18 21:44:51 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Debug: Check elements and map*/
static void	check_parse(t_data *data)
{
	printf("N -> '%s'\n", data->north.path);
	printf("S -> '%s'\n", data->south.path);
	printf("E -> '%s'\n", data->east.path);
	printf("W -> '%s'\n", data->west.path);
	printf("F -> '%i' '%i' '%i'\n", data->floor_rgb[0], data->floor_rgb[1], data->floor_rgb[2]);
	printf("C -> '%i' '%i' '%i'\n", data->ceiling_rgb[0], data->ceiling_rgb[1], data->ceiling_rgb[2]);
	
	int i = 0;

	printf("MAP (%d x %d):\n", data->map_width, data->map_height);
	while (data->map[i])
	{
		printf("[%s]\n", data->map[i]);
		i++;
	}
}

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

static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
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
	else
	{
		if (is_empty_line(line))
			return(error("invalid map: empty line inside map\n"));
		return (1);
	}
}

static int	read_lines(t_data *data, t_list **map_lines,
		int *map_started)
{
	char	*line;
	int		ret;

	line = get_next_line(data->fd);
	while (line)
	{
		charnull_gnl(line);
		ret = process_line(line, data, map_started);
		if (ret == -1)
		{
			free(line);
			clean_gnl(data->fd);
			return (-1);
		}
		if (ret == 1)
		{
			ft_lstadd_back(map_lines, ft_lstnew(line));
		}
		else
			free(line);
		line = get_next_line(data->fd);
	}
	return (0);
}

int	parse_file(t_data *data)
{
	int		map_started;
	t_list	*map_lines;
	int		result;

	map_started = 0;
	map_lines = NULL;
	if (read_lines(data, &map_lines, &map_started) == -1)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	if (!map_started)
	{
		ft_lstclear(&map_lines, free);
		return (error("no map found\n"));
	}
	if (!data->floor_set || !data->ceiling_set
		|| !data->north_set || !data->south_set
		|| !data->east_set || !data->west_set)
	{
		ft_lstclear(&map_lines, free);
		return (error("mising elements\n"));
	}
	data->floor_color = rgb_to_hex(data->floor_rgb);
	data->ceiling_color = rgb_to_hex(data->ceiling_rgb);
	result = parse_map(data, map_lines);
	check_parse(data);
	ft_lstclear(&map_lines, free);
	if (result == -1)
		return (-1);
	return (0);
}
