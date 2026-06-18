/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:07:26 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/18 21:50:40 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		error("malloc failed\n");
		return (NULL);
	}
	ft_bzero(data, sizeof(t_data));
	return (data);
}

int	init_fd(char **argv, t_data *data)
{
	int	fd;
	int	i;

	i = ft_strlen(argv[1]);
	if (i < 4 || ft_strncmp(argv[1] + i - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd(RED "Error: \n" RESET, 2);
		ft_putstr_fd("File not valid: insert 'map.cub'\n", 2);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(RED "Error: \n" RESET, 2);
		ft_putstr_fd("Cannot open file\n", 2);
		return (1);
	}
	data->fd = fd;
	return (0);
}

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

void	init_player(t_player *player)
{
	player->forward = 0;
	player->back = 0;
	player->left = 0;
	player->right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
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
