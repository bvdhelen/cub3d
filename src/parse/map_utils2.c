/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 13:39:49 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/17 20:14:13 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Verifica que todos los caracteres del mapa sean válidos.
 * Retorna 1 si encuentra algún carácter inválido, 0 si está bien. ketchup
 */
int	invalid_chars(t_data *data)
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
 * Cuenta cuántos jugadores hay y guarda la posición del primero.
 * Retorna el número de jugadores encontrados. ketchup
 */
int	count_player(t_data *data, int *px, int *py)
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
