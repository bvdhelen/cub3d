/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:36:01 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/05/04 20:34:26 by eldiaz-c         ###   ########.fr       */
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

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			cell = data->map[y][x];

			if (cell == '1')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 0x00FFFFFF);
			else if (cell == '0')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 0x00000000);
			x++;
		}
		y++;
	}
    draw_square(data, (int)data->pos_x * TILE_SIZE,
        (int)data->pos_y * TILE_SIZE, 0x000000FF);
}
