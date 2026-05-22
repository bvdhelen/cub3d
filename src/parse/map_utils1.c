/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:17:03 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/22 12:24:47 by bvdhelen         ###   ########.fr       */
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

/* Función que recibe data y la lista, construye el array y devuelvo 0 o -1 */
int	build_map_from_list(t_data *data, t_list *map_lines)
{
	int		i;
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
	return (pad_spaces(data));
}
