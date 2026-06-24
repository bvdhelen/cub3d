/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 17:35:17 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/24 17:36:24 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Bordes horizontales (arriba y abajo)
void	draw_h_border(t_data *data, int y, int x_start, int x_end, int color)
{
	int	x;

	if (y < 0 || y >= WIN_HEIGHT)
		return ;
	x = x_start;
	while (x <= x_end)
	{
		if (x >= 0 && x < WIN_WIDTH)
			put_pixel(data, x, y, color);
		x++;
	}
}

// Bordes verticales (izquierda y derecha, sin repetir esquinas)
void	draw_v_border(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;

	if (x < 0 || x >= WIN_WIDTH)
		return ;
	y = y_start;
	while (y <= y_end)
	{
		if (y >= 0 && y < WIN_HEIGHT)
			put_pixel(data, x, y, color);
		y++;
	}
}

void	draw_single_ray_2d(t_data *data, float dir_x, float dir_y)
{
	float	ray_x;
	float	ray_y;
	int		steps;
	int		sx;
	int		sy;
	int		hit_x;
	int		hit_y;

	ray_x = data->player.x;
	ray_y = data->player.y;
	steps = 0;
	while (!touch_wall(data, ray_x, ray_y) && steps < 200)
	{
		sx = (int)(ray_x * TILE_SIZE);
		sy = (int)(ray_y * TILE_SIZE);
		if (sx >= 0 && sx < WIN_WIDTH && sy >= 0 && sy < WIN_HEIGHT)
			put_pixel(data, sx, sy, 0x00FF00);
		ray_x += dir_x * 0.2f;
		ray_y += dir_y * 0.2f;
		steps++;
	}
	if (steps < 200)
	{
		hit_x = (int)(ray_x * TILE_SIZE);
		hit_y = (int)(ray_y * TILE_SIZE);
		put_pixel(data, hit_x, hit_y, 0xFF0000);
	}
}
