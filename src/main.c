/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:24:48 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/02 13:24:48 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		error_arg();
		return (1);
	}
	data = init_data();
	if (!data)
		//close (fd); ???
		return (1);
	if (init_fd(argv, data))
		return (1);
	if (parse_file(data) == -1)
	{
		close(data->fd);
		free_all(data);
		return (1);
	}
	if (!init_window(data))
		return (1);
	init_image(data);
	if (load_textures(data) == -1)
	{
		free_all(data);
		return (1);
	}
	hooks(data);
	mlx_loop_hook(data->mlx_connection, draw_loop, data);
	mlx_loop(data->mlx_connection);
	return (0);
}
