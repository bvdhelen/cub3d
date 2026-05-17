/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 13:39:49 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/17 13:53:24 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Flood fill recursivo.
 * - '1' y 'F' (ya visitado) son seguros.
 * - ' ' (espacio) significa que no hay pared -> error.
 * - Si sale de los límites del mapa -> error.
 * Retorna 1 si la celda es segura, 0 si encuentra un hueco.
 */
static int	flood_fill(char **map, int x, int y, int w, int h)
{
	if (x < 0 || x >= w || y < 0 || y >= h)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, w, h)
		|| !flood_fill(map, x - 1, y, w, h)
		|| !flood_fill(map, x, y + 1, w, h)
		|| !flood_fill(map, x, y - 1, w, h))
		return (0);
	return (1);
}

/*
 * Crea una copia del mapa y ejecuta el flood fill desde (px, py).
 * Retorna 1 si el mapa está cerrado, 0 si hay error.
 */
static int	check_closed(t_data *data, int px, int py)
{
	char	**copy;
	int		i;
	int		res;

	copy = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!copy)
		return (0);
	i = -1;
	while (++i < data->map_height)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			ft_freedp(copy);
			return (0);
		}
	}
	res = flood_fill(copy, px, py, data->map_width, data->map_height);
	ft_freedp(copy);
	return (res);
}

/*
 * Asigna los vectores de dirección y plano según el carácter del jugador.
 * Campo de visiónen Raycasting: entre 60º-90º
 * 0.66 = tan(30º) creo que si se puede usar math.h es mejor eso!!
 * https://lodev.org/cgtutor/raycasting.html
 */
static void	set_player_dir(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

// DEBUG HELPER
// static void	print_map(t_data *data)
// {
// 	int i = 0;

// 	printf("MAP (%d x %d):\n", data->map_width, data->map_height);
// 	while (data->map[i])
// 	{
// 		printf("[%s]\n", data->map[i]);
// 		i++;
// 	}
// }

/*
 * Función para rellenar con espacios.
 * Rellena cada línea del mapa con espacios hasta alcanzar map_width.
 * Retorna 0 en éxito, -1 si falla malloc.
 */
static int	pad_spaces(t_data *data)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < data->map_height)
	{
		new_line = malloc(data->map_width + 1);
		if (!new_line)
			return (-1);
		ft_memset(new_line, ' ', data->map_width);
		new_line[data->map_width] = '\0';
		ft_memcpy(new_line, data->map[i], ft_strlen(data->map[i]));
		free(data->map[i]);
		data->map[i] = new_line;
		i++;
	}
	return (0);
}

/*
 * Función principal parse_map:
 * 1. Construye la matriz data->map a partir de la lista map_lines.
 * 2. Valida caracteres, posición del jugador y cierre del mapa.
 * 	- Validación 0: rellenar la matriz con espacios
 *  - Validación 1: caracteres inválidos
 *  - Validación 2: un solo jugador
 * 		(Guardar la posición del jugador y sustituir por '0')
 *  - Validación 3: mapa cerrado
 * 3. Guarda la posición, orientación y vectores de dirección/plano.
 */
int	parse_map(t_data *data, t_list *map_lines)
{
	int		i;
	int		px;
	int		py;
	char	player;
	t_list	*tmp;

	data->map_height = count_lines(map_lines);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (-1);
	i = 0;
	tmp = map_lines;
	while (tmp)
	{
		data->map[i] = ft_strdup(trim_newline((char *)tmp->content));
		if (!data->map[i])
			return (-1);
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
	data->map_width = get_max_width(data);
	if (pad_spaces(data) == -1)
		return (-1);
	if (invalid_chars(data))
		return (error("Invalid map\tInvalid chars\n"));
	if (count_player(data, &px, &py) != 1)
		return (error("Invalid map\tInvalid number of players\n"));
	player = data->map[py][px];
	data->map[py][px] = '0';
	if (!check_closed(data, px, py))
		return (error("Invalid map\tMap not closed\n"));
	data->pos_x = px + 0.5;
	data->pos_y = py + 0.5;
	set_player_dir(data, player);
	return (0);
}
