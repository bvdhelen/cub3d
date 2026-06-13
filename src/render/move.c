/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:36:43 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/13 13:47:47 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//detecta si la posición actual de x e y toca la pared
int	touch_wall(t_data *data, float pos_x, float pos_y)
{
	int	x;
	int	y;

	if (pos_x < 0 || pos_y < 0)
		return (1);
	x = (int)(pos_x / TILE_SIZE);
	y = (int)(pos_y / TILE_SIZE);
	if (y >= data->map_height || x >= data->map_width)
		return (1);
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

void	move_vector(t_data *data, t_player *player, float move_x, float move_y)
{
	float	new_x;
	float	new_y;
	int		angle_step;
	float	angle;
	float	check_x;
	float	check_y;
	int		colision_x = 0;
	int		colision_y = 0;

	new_x = player->x + move_x * MOVE_SPEED;
	new_y = player->y + move_y * MOVE_SPEED;
	// Comprobar colisión circular: muestrear puntos alrededor del perímetro
	angle_step = 12;  // número de puntos a comprobar (cuantos más, más preciso)
	
	// Movimiento en X (horizontal)
	angle = 0;
	while (angle < 2 * PI)
	{
		check_x = new_x + cosf(angle) * PLAYER_RADIUS;
		check_y = player->y + sinf(angle) * PLAYER_RADIUS;
		if (touch_wall(data, check_x, check_y))
		{
			colision_x = 1;
			break ;
		}
		angle += 2 * PI / angle_step;
	}
	// Sin colisión, actualizar posición
	if (!colision_x)
		player->x = new_x;
	
	// Movimiento en Y (vertical)
	angle = 0;
	while (angle < 2 * PI)
	{
		check_x = player->x + cosf(angle) * PLAYER_RADIUS;
		check_y = new_y + sinf(angle) * PLAYER_RADIUS;
		if (touch_wall(data, check_x, check_y))
		{
			colision_y = 1;
			break ;
		}
		angle += 2 * PI / angle_step;
	}
	// Sin colisión, actualizar posición
	if (!colision_y)
		player->y = new_y;
}

// void	move_vector(t_data *data, t_player *player, float move_x, float move_y)
// {
// 	int		speed;
// 	float	next_x;
// 	float	next_y;

// 	speed = 3;
// 	next_x = player->x + move_x * speed;
// 	next_y = player->y + move_y * speed;

// 	int radius = PLAYER_SIZE / 2;

// 	// if (!touch_wall(data, next_x + PLAYER_RADIUS, player->y)
// 	// 	&& !touch_wall(data, next_x - PLAYER_RADIUS, player->y))
// 	// 	player->x = next_x;

// 	// if (!touch_wall(data, player->x, next_y + PLAYER_RADIUS)
// 	// 	&& !touch_wall(data, player->x, next_y - PLAYER_RADIUS))
// 	// 	player->y = next_y;
// 	if (!touch_wall(data, next_x - radius, player->y - radius)
// 		&& !touch_wall(data, next_x + radius, player->y - radius)
// 		&& !touch_wall(data, next_x - radius, player->y + radius)
// 		&& !touch_wall(data, next_x + radius, player->y + radius))
// 		player->x = next_x;

// 	if (!touch_wall(data, player->x - radius, next_y - radius)
// 		&& !touch_wall(data, player->x + radius, next_y - radius)
// 		&& !touch_wall(data, player->x - radius, next_y + radius)
// 		&& !touch_wall(data, player->x + radius, next_y + radius))
// 		player->y = next_y;
	
// 	// if (!touch_wall(data, next_x + PLAYER_SIZE / 2, player->y)
// 	// && !touch_wall(data, next_x - PLAYER_SIZE / 2, player->y))
// 	// 	player->x = next_x;
// 	// if (!touch_wall(data, player->x, next_y + PLAYER_SIZE / 2)
// 	// && !touch_wall(data, player->x, next_y - PLAYER_SIZE / 2))
// 	// 	player->y = next_y;
// }

void	move_player(t_data *data, t_player *player)
{
	float	cos_angle;
	float	sin_angle;
	float 	move_x = 0;
	float 	move_y = 0;
	float	len;

	move_x = 0;
	move_y = 0;
	// Rotación
	if (player->rotate_left)
		player->angle -= ROTATE_SPEED;
	if (player->rotate_right)
		player->angle += ROTATE_SPEED;
	// Ajustar ángulo dentro de [0, 2*PI]
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	cos_angle = cosf(player->angle);
	sin_angle = sinf(player->angle);
	// Acumular dirección de movimiento
	if (player->forward)
	{
		move_x += cos_angle;
		move_y += sin_angle;
	}
	if (player->back)
	{
		move_x -= cos_angle;
		move_y -= sin_angle;
	}
	if (player->left)
	{
		move_x += sin_angle;
		move_y -= cos_angle;
	}
	if (player->right)
	{
		move_x -= sin_angle;
		move_y += cos_angle;
	}
	// Normalizar para que la velocidad sea constante en cualquier dirección
	len = sqrtf(move_x * move_x + move_y * move_y);
	if (len > 0.001f)
	{
		move_x /= len;
		move_y /= len;
	}
	// Aplicar el movimiento
	move_vector(data, player, move_x, move_y);
}
