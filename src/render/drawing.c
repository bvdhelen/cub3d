/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:23:33 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/24 17:55:13 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(data, x, y, 0);
			x++;
		}
		y++;
	}
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
	int		color;
	int		y;
	int		x;

	color = 0xFF0099;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, float cell_x, float cell_y, int color)
{
	int	px;
	int	py;
	int	half;

	px = (int)(cell_x * TILE_SIZE);
	py = (int)(cell_y * TILE_SIZE);
	half = PLAYER_SIZE / 2;
	draw_h_border(data, py - half, px - half, px + half, color);
	draw_h_border(data, py + half, px - half, px + half, color);
	draw_v_border(data, px - half, py - half + 1, py + half - 1, color);
	draw_v_border(data, px + half, py - half + 1, py + half - 1, color);
}

/* Dibuja en 2D todos los rayos */
// Dibujamos un rayo cada 2 píxeles de ancho de pantalla
// Avanzar mientras no toque pared y no salga del mapa (máximo 200 pasos)
// Punto de impacto (rojo)
void	draw_all_rays_2d(t_data *data)
{
	t_ray2d	r;

	r.cos_angle = cosf(data->player.angle);
	r.sin_angle = sinf(data->player.angle);
	r.plane_x = -r.sin_angle * 0.66f;
	r.plane_y = r.cos_angle * 0.66f;
	r.x = 0;
	while (r.x < WIN_WIDTH)
	{
		r.camera_x = 2.0f * r.x / WIN_WIDTH - 1.0f;
		r.ray_dir_x = r.cos_angle + r.plane_x * r.camera_x;
		r.ray_dir_y = r.sin_angle + r.plane_y * r.camera_x;
		draw_single_ray_2d(data, r.ray_dir_x, r.ray_dir_y);
		r.x += 2;
	}
}
