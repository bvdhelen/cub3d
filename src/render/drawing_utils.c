/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 17:35:17 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/24 19:45:38 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Bordes horizontales (arriba y abajo)
void	draw_h_border(t_data *data, t_border b)
{
	int	x;

	if (b.pos < 0 || b.pos >= WIN_HEIGHT)
		return ;
	x = b.start;
	while (x <= b.end)
	{
		if (x >= 0 && x < WIN_WIDTH)
			put_pixel(data, x, b.pos, b.color);
		x++;
	}
}

// Bordes verticales (izquierda y derecha, sin repetir esquinas)
void	draw_v_border(t_data *data, t_border b)
{
	int	y;

	if (b.pos < 0 || b.pos >= WIN_WIDTH)
		return ;
	y = b.start;
	while (y <= b.end)
	{
		if (y >= 0 && y < WIN_HEIGHT)
			put_pixel(data, b.pos, y, b.color);
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
		put_pixel(data,
			(int)(ray_x * TILE_SIZE), (int)(ray_y * TILE_SIZE), 0xFF0000);
}
