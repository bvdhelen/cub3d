/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:36:43 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/18 20:53:00 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//COLISIONES EN 2D CON EL CUADRADO
void	move_vector(t_data *data, t_player *player, float move_x, float move_y)
{
	float	new_x;
	float	new_y;
	float	half;

	new_x = player->x + move_x * MOVE_SPEED;
	new_y = player->y + move_y * MOVE_SPEED;
	half = (PLAYER_SIZE / 2.0f) / TILE_SIZE;//medio lado en celdas
	// Movimiento en X
	if (!touch_wall(data, new_x - half, player->y - half)
		&& !touch_wall(data, new_x + half, player->y - half)
		&& !touch_wall(data, new_x - half, player->y + half)
		&& !touch_wall(data, new_x + half, player->y + half))
		player->x = new_x;
	// Movimiento en Y
	if (!touch_wall(data, player->x - half, new_y - half)
		&& !touch_wall(data, player->x + half, new_y - half)
		&& !touch_wall(data, player->x - half, new_y + half)
		&& !touch_wall(data, player->x + half, new_y + half))
		player->y = new_y;
}

static void	update_angle(t_player *player)
{
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
}

void	add_move(float *move_x, float *move_y, float next_x, float next_y)
{
	*move_x += next_x;
	*move_y += next_y;
}

static void	get_move_direction(t_player *player, float *move_x, float *move_y)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cosf(player->angle);
	sin_angle = sinf(player->angle);
	*move_x = 0;
	*move_y = 0;
	if (player->forward)
		add_move(move_x, move_y, cos_angle, sin_angle);
	if (player->back)
		add_move(move_x, move_y, -cos_angle, -sin_angle);
	if (player->left)
		add_move(move_x, move_y, sin_angle, -cos_angle);
	if (player->right)
		add_move(move_x, move_y, -sin_angle, cos_angle);
}

void	move_player(t_data *data, t_player *player)
{
	float	move_x;
	float	move_y;
	float	len;

	move_x = 0;
	move_y = 0;
	update_angle(player);
	get_move_direction(player, &move_x, &move_y);
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

// COLISIONES EN 2D CON RADIO
// void	move_vector(t_data *data, t_player *player, float move_x, float move_y)
// {
// 	float	new_x;
// 	float	new_y;
// 	int		angle_step;
// 	float	angle;
// 	float	check_x;
// 	float	check_y;
// 	int		colision_x = 0;
// 	int		colision_y = 0;

// 	new_x = player->x + move_x * MOVE_SPEED;
// 	new_y = player->y + move_y * MOVE_SPEED;
// 	// Comprobar colisión circular: muestrear puntos alrededor del perímetro
// 	angle_step = 16;  // número de puntos a comprobar (cuantos más, más preciso)
	
// 	// Movimiento en X (horizontal)
// 	angle = 0;
// 	while (angle < 2 * PI)
// 	{
// 		check_x = new_x + cosf(angle) * PLAYER_RADIUS_CELL;
// 		check_y = player->y + sinf(angle) * PLAYER_RADIUS_CELL;
// 		if (touch_wall(data, check_x, check_y))
// 		{
// 			colision_x = 1;
// 			break ;
// 		}
// 		angle += 2 * PI / angle_step;
// 	}
// 	// Sin colisión, actualizar posición
// 	if (!colision_x)
// 		player->x = new_x;
	
// 	// Movimiento en Y (vertical)
// 	angle = 0;
// 	while (angle < 2 * PI)
// 	{
// 		check_x = player->x + cosf(angle) * PLAYER_RADIUS_CELL;
// 		check_y = new_y + sinf(angle) * PLAYER_RADIUS_CELL;
// 		if (touch_wall(data, check_x, check_y))
// 		{
// 			colision_y = 1;
// 			break ;
// 		}
// 		angle += 2 * PI / angle_step;
// 	}
// 	// Sin colisión, actualizar posición
// 	if (!colision_y)
// 		player->y = new_y;
// }
