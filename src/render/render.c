/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:35:58 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/12 16:08:47 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

//corrige la distancia para obtener la distancia perpendicular al plano: no fish-eye
float	get_corrected_distance(t_player *player, float hit_x, float hit_y)
{
	float	x_offset;//separación horizontal
	float	y_offset;//separación vertical
	float	angle_difference;//diferencia angular
	float	real_distance;//distancia real * cos(diferencia angular); cateto = hipotenusa * cos(angulo)

	x_offset = hit_x - player->x;
	y_offset = hit_y - player->y;
	angle_difference = atan2(y_offset, x_offset) - player->angle;
	real_distance = get_distance(x_offset, y_offset) * cos(angle_difference);
	return (real_distance);
}
/*		-------------x----wall
	y_offset|	   /
			|    / -> hipotenusa (distancia a corregir)
			|  /
			x _ _ _ x_offset
			jugador
*///borrar cuando lo vea elena

// altura_pared = (TILE_SIZE / distancia_perpendicular) * distancia_al_plano
void	draw_surfaces(t_data *data, float distance, int x)
{
	int		y;
	int		end_y;
	int		start_y;
	float	height;
	float	plane_dist;

	// Distancia al plano de proyección (evita el ojo de pez)
	plane_dist = (WIN_WIDTH / 2.0f) / tanf(FOV / 2.0f);
	// Altura de la pared en píxeles
	height = (TILE_SIZE / distance) * plane_dist;
	// Limitar altura para valores extremos
	if (height > WIN_HEIGHT * 2)
		height = WIN_HEIGHT * 2;
	start_y = (WIN_HEIGHT - height) / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = start_y + height;
	if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	// Techo
	y = 0;
	while (y < start_y)
	{
		put_pixel(data, x, y, data->ceiling_color);
		y++;
	}
	// Pared (de momento color, luego texturas)
	while (y < end_y)
	{
		put_pixel(data, x, y, 0x808080);
		y++;
	}
	// Suelo
	while (y < WIN_HEIGHT)
	{
		put_pixel(data, x, y, data->floor_color);
		y++;
	}
}

void	draw_wall(t_data *data, t_player *player, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	float	distance;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch_wall(data, ray_x, ray_y))
	{
		if (CUB2D)
			put_pixel(data, ray_x, ray_y, 0x00FF00);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!CUB2D)
	{
		//distance = get_distance(ray_x - player->x, ray_y - player->y);//fish eye por si elena lo quiere ver; si no borrar línea entera
		distance = get_corrected_distance(player, ray_x, ray_y);
		draw_surfaces(data, distance, i);
	}
}

int	draw_loop(t_data *data)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	// if (frame_limit())
	// 	return (0);
	player = &data->player;
	move_player(data, player);
	if (CUB2D)
	{
		clear_image(data);
		//draw_map(data);
		draw_mapaa(data);
		//draw_square(data, player->x, player->y, 0xFF7FB7);
		draw_player(data, player->x, player->y, 0xFFDA20);
	}
	fraction = FOV / WIN_WIDTH;
	start_x = player->angle - FOV / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_wall(data, player, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(data->mlx_connection, data->window,
		data->imagen.img, 0, 0);
	return (0);
}
