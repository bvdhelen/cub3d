/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:14:54 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/11 21:20:12 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_addr(t_data *data)
{
	if (data->north.addr)
		free(data->north.addr);
	if (data->south.addr)
		free(data->south.addr);
	if (data->east.addr)
		free(data->east.addr);
	if (data->west.addr)
		free(data->west.addr);
}

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
	// if (data->north.path)
	// 	free(data->north.path);
	// if (data->south.path)
	// 	free(data->south.path);
	// if (data->east.path)
	// 	free(data->east.path);
	// if (data->west.path)
	// 	free(data->west.path);
	free_textures_addr(data);
	if (data->imagen.img)
		mlx_destroy_image(data->mlx_connection, data->imagen.img);
	if (data->window)
		mlx_destroy_window(data->mlx_connection, data->window);
	if (data->mlx_connection)
	{
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
	}
	close(data->fd);
	free(data);
}
