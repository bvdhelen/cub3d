/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:37:04 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/13 21:21:11 by bvdhelen         ###   ########.fr       */
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
	long	current_time_ms;

	gettimeofday(&tv, NULL);
	current_time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	static long	last_frame = 0;
	// long		current;

	// current = frame_limit();

	if (current_time_ms - last_frame < 41)
		return (1);

	last_frame = current_time_ms;
	return (0);
}
