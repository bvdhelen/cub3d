/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:45:50 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/02 13:34:39 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int	get_max_width(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
		i++;
	}
	return (max);
}

/*
 * Cuenta cuántos jugadores hay y guarda la posición del primero.
 * Retorna el número de jugadores encontrados.
 */
static int	count_player(t_data *data, int *px, int *py)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (ft_strchr("NSEW", data->map[i][j]))
			{
				count++;
				*px = j;
				*py = i;
			}
		}
	}
	return (count);
}

/*
 * Verifica que todos los caracteres del mapa sean válidos.
 * Retorna 1 si encuentra algún carácter inválido, 0 si está bien.
 */
static int	invalid_chars(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (!ft_strchr("01NSEW ", data->map[i][j]))
				return (1);
		}
	}
	return (0);
}

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

/*
 * Función principal parse_map:
 * 1. Construye la matriz data->map a partir de la lista map_lines.
 * 2. Valida caracteres, posición del jugador y cierre del mapa.
 * 3. Guarda la posición, orientación y vectores de dirección/plano.
 */
int	parse_map(t_data *data, t_list *map_lines)
{
	int		i;
	int		px, py;
	char	player;
	t_list	*tmp;

	// Construcción de data->map
	data->map_height = count_lines(map_lines);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (-1);
	i = 0;
	tmp = map_lines;
	while (tmp)
	{
        // ¿el gnl de Pau tiene '\n' o ya no? SI no lo tiene, trim.. no necesario
		data->map[i] = ft_strdup(trim_newline((char *)tmp->content));
		if (!data->map[i])
			return (-1);
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
	data->map_width = get_max_width(data);
    // FUNCION PARA RELLENAR CON ESPACIOS
    for (int idx = 0; idx < data->map_height; idx++)
    {
        char *new_line = malloc(data->map_width + 1);
        if (!new_line)
            return (-1);
        ft_memset(new_line, ' ', data->map_width);
        new_line[data->map_width] = '\0';
        ft_memcpy(new_line, data->map[idx], ft_strlen(data->map[idx]));
        free(data->map[idx]);
        data->map[idx] = new_line;
    }
	// Validación 1: caracteres inválidos
	if (invalid_chars(data))
		return (-1);
	// Validación 2: un solo jugador
	if (count_player(data, &px, &py) != 1)
		return (-1);
	// !!Guardamos la posición del jugador y lo sustituimos por '0' (para que se pueda caminar)
	player = data->map[py][px];
	data->map[py][px] = '0';
	// Validación 3: mapa cerrado
	if (!check_closed(data, px, py))
		return (-1);
	// !! Posición EXACTA del jugador en pix (centro de la celda)
	data->pos_x = px + 0.5;
	data->pos_y = py + 0.5;
	set_player_dir(data, player);
	return (0);
}
