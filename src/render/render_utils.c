/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:37:04 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/18 20:53:10 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	pixel = data->imagen.addr
		+ (y * data->imagen.line_length
			+ x * (data->imagen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	frame_limit(void)
{
	struct timeval	tv;
	long			current_time_ms;
	static long		last_frame = 0;

	gettimeofday(&tv, NULL);
	current_time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (current_time_ms - last_frame < 41)
		return (1);
	last_frame = current_time_ms;
	return (0);
}

//detecta si la posición actual de x e y toca la pared
int	touch_wall(t_data *data, float pos_x, float pos_y)
{
	int	x;
	int	y;

	if (pos_x < 0 || pos_y < 0)
		return (1);
	x = (int)pos_x;
	y = (int)pos_y;
	if (y >= data->map_height || x >= data->map_width)
		return (1);
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}
