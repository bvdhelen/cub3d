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
	int		i;//COMPROBAR LÍNEA 26-34 ketchup

	if (argc != 2)
	{
		error_arg();
		return (1);
	}
	//HACER COMPROBACIÓN DE SI NO ES .CUB NO ENTRAR:ketchup
	i = ft_strlen(argv[1]);
	if (i < 4 || ft_strncmp(argv[1] + i - 4, ".cub", 4) != 0)//ver bien porque es diferente a la de parse_elements
	{
		ft_putstr_fd(RED "Error: \n" RESET, 2);
		ft_putstr_fd("File not valid: insert 'map.cub'\n", 2);//preguntar a elena
		return (1);
	}
	//COMPROBAR LO DE ARRIBA
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
	init_set(data);//ketchup
	if (parse_file(fd, data) == -1)
	{
		close(fd);
		free_all(data);
		return (1);
	}
	if (!init_window(data))
		return (1);
	init_image(data);
	//Aqui hace cosas
	draw_map(data);
	mlx_put_image_to_window(data->mlx_connection, data->window,
		data->imagen.img, 0, 0);
	//display_instructions(data);
	mlx_key_hook(data->window, handle_key, data);
	mlx_hook(data->window, 17, 0, handle_event, data);
	mlx_loop(data->mlx_connection);
	
	//start_game(&data);
	//free_game(&data);
	close(fd);
	free_all(data);
	return (0);
}
