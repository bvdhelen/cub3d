/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:07:26 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/13 19:56:54 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*ketchup
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
    ft_bzero(data, sizeof(t_data));
	data->fd = -1;
	return (data);
}

//¿creo que es redundante y sobra?
// void	init_set(t_data *data)
// {
// 	data->floor_set = 0;
// 	data->ceiling_set = 0;
// 	data->north_set = 0;
// 	data->south_set = 0;
// 	data->east_set = 0;
// 	data->west_set = 0;
// }

int	init_window(t_data *data)
{
    data->mlx_connection = mlx_init();
	if (!data->mlx_connection)
		return (0);
	data->window = mlx_new_window(data->mlx_connection,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->window)
	{
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
		return (0);
	}
	return (1);
}

void	init_image(t_data *data)
{
	init_player(&data->player);
	if (data->imagen.img)
		mlx_destroy_image(data->mlx_connection, data->imagen.img);
	data->imagen.img = mlx_new_image(data->mlx_connection,
			WIN_WIDTH, WIN_HEIGHT);
	if (!data->imagen.img)
	{
		free_all(data);
		error("imagen init failed\n");
		return ;
	}
	data->imagen.addr = mlx_get_data_addr(data->imagen.img,
			&data->imagen.bits_per_pixel, &data->imagen.line_length,
			&data->imagen.endian);
	if (!data->imagen.addr)
	{
		free_all(data);
		error("imagen pixel address failed\n");
		return ;
	}
}

void	init_player(t_player *player)
{
	player->forward = 0;
	player->back = 0;
	player->left = 0;
	player->right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
}
