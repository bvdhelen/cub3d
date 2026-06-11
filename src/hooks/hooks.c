/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:18:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/11 21:17:01 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	release_key(int key, t_player *player)
{
	if (key == XK_w)
		player->forward = 0;
	if (key == XK_s)
		player->back = 0;
	if (key == XK_a)
		player->left = 0;
	if (key == XK_d)
		player->right = 0;
	if (key == XK_Left)
		player->rotate_left = 0;
	if (key == XK_Right)
		player->rotate_right = 0;
	return (0);
}

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		ft_putstr_fd(GREY "Program closed using the 'ESC' key\n" RESET, 1);
		free_all(data);
		exit(0);
	}
	if (key == XK_w)
		data->player.forward = 1;
	if (key == XK_s)
		data->player.back = 1;
	if (key == XK_a)
		data->player.left = 1;
	if (key == XK_d)
		data->player.right = 1;
	if (key == XK_Left)
		data->player.rotate_left = 1;
	if (key == XK_Right)
		data->player.rotate_right = 1;
	return (0);
}

int	handle_event(t_data *data)
{
	ft_putstr_fd(GREY "Program closed using the 'x' button\n" RESET, 1);
	free_all(data);
	exit(0);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->window, 17, 1L << 17, handle_event, data);
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 3, 1L << 1, release_key, &data->player);
}
