/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:14:54 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/19 23:34:47 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *data)
{
	if (data->north.path)
		free(data->north.path);
	if (data->south.path)
		free(data->south.path);
	if (data->east.path)
		free(data->east.path);
	if (data->west.path)
		free(data->west.path);
	if (data->north.img)
		mlx_destroy_image(data->mlx_connection, data->north.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx_connection, data->south.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx_connection, data->east.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx_connection, data->west.img);
}

void	free_all(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map)
	{
		i = 0;
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	free_textures(data);
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
