/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:45:50 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/17 13:40:32 by bvdhelen         ###   ########.fr       */
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
