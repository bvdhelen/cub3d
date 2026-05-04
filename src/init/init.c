/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:07:26 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/04 19:42:45 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	set_default_values(t_data *data)
// {
// 	data->map = NULL;
// 	data->map_width = 0;
// 	data->map_height = 0;

// 	data->mlx_connection = NULL;
// 	data->window = NULL;

//     data->imagen.img = NULL;
// 	data->imagen.addr = NULL;
// 	data->imagen.bits_per_pixel = 0;
// 	data->imagen.line_length = 0;
// 	data->imagen.endian = 0;
    
// 	data->pos_x = -1;
// 	data->pos_y = -1;
// }

/*
    init_data      → malloc + defaults
    init_window    → mlx_init + ventana
    init_image     → imagen principal
*/
t_data	*init_data(void)
{
    t_data  *data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		error("malloc failed\n");
        return (NULL);
	}
		//"Error al reservar memoria para t_data.\n"
    ft_bzero(data, sizeof(t_data));
    //set_default_values(data);
	//free(data);
	return (data);
}

int	init_window(t_data *data)
{
    data->mlx_connection = mlx_init();
	if (!data->mlx_connection)
		return (0);
	data->window = mlx_new_window(data->mlx_connection, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->window)
	{
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
		return (0);
	}
	return (1);
}

void	init_image(t_data *data, int width, int height)
{
	if (data->imagen.img)
		mlx_destroy_image(data->mlx_connection, data->imagen.img);
	data->imagen.img = mlx_new_image(data->mlx_connection, width, height);
	if (!data->imagen.img)
	{
		error("imagen init failed\n");
		return ;
		//free_all(data);
	}
	data->imagen.addr = mlx_get_data_addr(data->imagen.img,
			&data->imagen.bits_per_pixel, &data->imagen.line_length, &data->imagen.endian);
	if (!data->imagen.addr)
	{
		error("imagen pixel address failed\n");
		return ;
		//free_all(data);
	}
}
