/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:18:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/05/04 19:02:24 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		ft_putstr_fd(GREY "Program closed using the 'ESC' key\n" RESET, 1);
		free_all(data);
		exit(0);
	}
	// movement_and_rotation_keys(key, data);
	// zoom_and_flatten_keys(key, data);
	// projection_and_center_keys(key, data);
	init_image(data, WIN_WIDTH, WIN_HEIGHT);
	mlx_clear_window(data->mlx_connection, data->window);
	// draw(data);
	mlx_put_image_to_window(data->mlx_connection, data->window,
		data->imagen.img, 0, 0);
	// display_instructions(data);
	return (0);
}

int	handle_event(t_data *data)
{
	ft_putstr_fd(GREY "Program closed using the 'x' button\n" RESET, 1);
	free_all(data);
	exit(0);
	return (0);
}
