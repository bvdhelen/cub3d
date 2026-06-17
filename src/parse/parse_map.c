/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:45:50 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/17 20:32:15 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Flood fill recursivo.
 * - '1' y 'F' (ya visitado) son seguros.
 * - ' ' (espacio) significa que no hay pared -> error.
 * - Si sale de los límites del mapa -> error.
 * Retorna 1 si la celda es segura, 0 si encuentra un hueco.ketchup
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
 * Retorna 1 si el mapa está cerrado, 0 si hay error.ketchup
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

/* Asigna los vectores de dirección y plano según el
carácter del jugador.ketchup*/
static void	set_player_angle(t_data *data, char dir)
{
	if (dir == 'N')
		data->player.angle = 3 * PI / 2;
	if (dir == 'S')
		data->player.angle = PI / 2;
	if (dir == 'E')
		data->player.angle = 0;
	if (dir == 'W')
		data->player.angle = PI;
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
 * 3. Guarda la posición, orientación y vectores de dirección/plano.ketchup
 */
int	parse_map(t_data *data, t_list *map_lines)
{
	int		px;
	int		py;
	char	player;

	if (build_map_from_list(data, map_lines) == -1)
		return (-1);
	if (invalid_chars(data))
		return (error("invalid map: invalid chars\n"));
	if (count_player(data, &px, &py) != 1)
		return (error("invalid map: invalid number of players\n"));
	player = data->map[py][px];
	data->map[py][px] = '0';
	if (!check_closed(data, px, py))
		return (error("invalid map: map not closed\n"));
	data->player.x = px + 0.5;
	data->player.y = py + 0.5;
	set_player_angle(data, player);
	return (0);
}
