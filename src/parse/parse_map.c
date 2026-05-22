/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:45:50 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/22 12:30:39 by bvdhelen         ###   ########.fr       */
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
static int	flood_fill(t_flood *f, int x, int y)
{
	if (x < 0 || x >= f->w || y < 0 || y >= f->h)
		return (0);
	if (f->map[y][x] == '1' || f->map[y][x] == 'F')
		return (1);
	if (f->map[y][x] == ' ')
		return (0);
	f->map[y][x] = 'F';
	if (!flood_fill(f, x + 1, y)
		|| !flood_fill(f, x - 1, y)
		|| !flood_fill(f, x, y + 1)
		|| !flood_fill(f, x, y - 1))
		return (0);
	return (1);
}

/*
 * Crea una copia del mapa y ejecuta el flood fill desde (px, py).
 * Retorna 1 si el mapa está cerrado, 0 si hay error.
 */
int	check_closed(t_data *data, int px, int py)
{
	char	**copy;
	int		i;
	t_flood	f;

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
	f.map = copy;
	f.w = data->map_width;
	f.h = data->map_height;
	i = flood_fill(&f, px, py);
	ft_freedp(copy);
	return (i);
}

/*
 * Asigna los vectores de dirección y plano según el carácter del jugador.
 * Campo de visiónen Raycasting: entre 60º-90º
 * 0.66 = tan(30º) creo que si se puede usar math.h es mejor eso!!
 * https://lodev.org/cgtutor/raycasting.html
 */
static void	set_player_dir_ns(t_data *data, char dir)
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
}

static void	set_player_dir_ew(t_data *data, char dir)
{
	if (dir == 'E')
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
	int		px;
	int		py;
	char	player;

	if (build_map_from_list(data, map_lines) == -1)
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
	if (player == 'N' || player == 'S')
		set_player_dir_ns(data, player);
	else
		set_player_dir_ew(data, player);
	return (0);
}
