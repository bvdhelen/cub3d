/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:23:33 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/18 21:03:02 by ptrapero         ###   ########.fr       */
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
	int	px = (int)(cell_x * TILE_SIZE);
	int	py = (int)(cell_y * TILE_SIZE);
	int	half = PLAYER_SIZE / 2;
	int	start_x = px - half;
	int	start_y = py - half;
	int	end_x = px + half;
	int	end_y = py + half;

	// Bordes horizontales (arriba y abajo)
	for (int x = start_x; x <= end_x; x++)
	{
		if (x >= 0 && x < WIN_WIDTH && start_y >= 0 && start_y < WIN_HEIGHT)
			put_pixel(data, x, start_y, color);
		if (x >= 0 && x < WIN_WIDTH && end_y >= 0 && end_y < WIN_HEIGHT)
			put_pixel(data, x, end_y, color);
	}
	// Bordes verticales (izquierda y derecha, sin repetir esquinas)
	for (int y = start_y + 1; y < end_y; y++)
	{
		if (start_x >= 0 && start_x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			put_pixel(data, start_x, y, color);
		if (end_x >= 0 && end_x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			put_pixel(data, end_x, y, color);
	}
}

/* Dibuja en 2D todos los rayos */
void	draw_all_rays_2d(t_data *data)
{
	t_player	*p = &data->player;
	float		cos_angle = cosf(p->angle);
	float		sin_angle = sinf(p->angle);
	float		plane_x = -sin_angle * 0.66f;
	float		plane_y = cos_angle * 0.66f;
	float		ray_x, ray_y;
	int			steps;

	// Dibujamos un rayo cada 2 píxeles de ancho de pantalla
	for (int x = 0; x < WIN_WIDTH; x += 2)
	{
		float	camera_x = 2.0f * x / WIN_WIDTH - 1.0f;
		float	ray_dir_x = cos_angle + plane_x * camera_x;
		float	ray_dir_y = sin_angle + plane_y * camera_x;

		ray_x = p->x;
		ray_y = p->y;
		steps = 0;
		// Avanzar mientras no toque pared y no salga del mapa (máximo 200 pasos)
		while (!touch_wall(data, ray_x, ray_y) && steps < 200)
		{
			int	sx = (int)(ray_x * TILE_SIZE);
			int	sy = (int)(ray_y * TILE_SIZE);
			if (sx >= 0 && sx < WIN_WIDTH && sy >= 0 && sy < WIN_HEIGHT)
				put_pixel(data, sx, sy, 0x00FF00);
			ray_x += ray_dir_x * 0.2f;
			ray_y += ray_dir_y * 0.2f;
			steps++;
		}
		// Punto de impacto (rojo)
		if (steps < 200)
		{
			int	hit_x = (int)(ray_x * TILE_SIZE);
			int	hit_y = (int)(ray_y * TILE_SIZE);
			put_pixel(data, hit_x, hit_y, 0xFF0000);
		}
	}
}	
