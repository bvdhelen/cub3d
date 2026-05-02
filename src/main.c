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

	if (argc != 2)
	{
		error_arg();
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
	if (parse_file(fd, data) == -1)
	{
		close(fd);
		free_data(data);
		free(data);
		return (1);
	}
	close(fd);
	printf("Mapa parseado correctamente:\n");
	for (int i = 0; data->map[i]; i++)
		printf("%s\n", data->map[i]);
	//start_game(&data);
	//free_game(&data);
	free_data(data);
	free(data);
	return (0);
}
