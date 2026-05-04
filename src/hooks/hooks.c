/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:18:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/05/04 20:40:36 by eldiaz-c         ###   ########.fr       */
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
    // + teclas
	return (0);
}

int	handle_event(t_data *data)
{
	ft_putstr_fd(GREY "Program closed using the 'x' button\n" RESET, 1);
	free_all(data);
	exit(0);
	return (0);
}
