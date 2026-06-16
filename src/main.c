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
	int		fd;
	int		i;

	if (argc != 2)
	{
		error_arg();
		return (1);
	}
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
    data = init_data();
	if (!data)
	{
		close(fd);
		return (1);
	}
	data->fd = fd;
	if (parse_file(fd, data) == -1)
	{
		close(fd);
		free_all(data);
		return (1);
	}
	if (!init_window(data))
		return (1);
	init_image(data);
	hooks(data);
	mlx_loop_hook(data->mlx_connection, draw_loop, data);
	mlx_loop(data->mlx_connection);
	return (0);
}
