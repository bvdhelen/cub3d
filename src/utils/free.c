/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:14:54 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/22 11:47:28 by bvdhelen         ###   ########.fr       */
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
	if (data->north.path)
		free(data->north.path);
	if (data->south.path)
		free(data->south.path);
	if (data->east.path)
		free(data->east.path);
	if (data->west.path)
		free(data->west.path);
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
