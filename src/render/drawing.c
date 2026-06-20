/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:23:33 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/20 17:39:35 by bvdhelen         ###   ########.fr       */
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

static void	draw_single_ray_2d(t_data *data, float dir_x, float dir_y)
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

/* Dibuja en 2D todos los rayos */
// Dibujamos un rayo cada 2 píxeles de ancho de pantalla
// Avanzar mientras no toque pared y no salga del mapa (máximo 200 pasos)
// Punto de impacto (rojo)
void	draw_all_rays_2d(t_data *data)
{
	float	cos_angle;
	float	sin_angle;
	float	plane_x;
	float	plane_y;
	int		x;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;

	cos_angle = cosf(data->player.angle);
	sin_angle = sinf(data->player.angle);
	plane_x = -sin_angle * 0.66f;
	plane_y = cos_angle * 0.66f;
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2.0f * x / WIN_WIDTH - 1.0f;
		ray_dir_x = cos_angle + plane_x * camera_x;
		ray_dir_y = sin_angle + plane_y * camera_x;
		draw_single_ray_2d(data, ray_dir_x, ray_dir_y);
		x += 2;
	}
}
