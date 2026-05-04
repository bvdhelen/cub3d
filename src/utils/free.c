/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:14:54 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/04 20:37:12 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_all(t_data *data)
{
	int i;

	if (!data)
		return ;
	if (data->map)
	{
		i = 0;
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	// free texturas???
		// Cuando carguemos las texturas, las liberaremos aquí
	if (data->imagen.img)
		mlx_destroy_image(data->mlx_connection, data->imagen.img);
	if (data->window)
		mlx_destroy_window(data->mlx_connection, data->window);
	if (data->mlx_connection)
	{
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
	}
	free(data);
}
