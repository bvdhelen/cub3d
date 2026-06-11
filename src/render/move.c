/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:36:43 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/11 19:33:30 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//detecta si la posición actual de x e y toca la pared
int	touch_wall(t_data *data, float pos_x, float pos_y)
{
	int	x;
	int	y;

	x = pos_x / TILE_SIZE;
	y = pos_y / TILE_SIZE;
	if (y < 0 || data->map[y] == NULL)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (1);
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

void	move_vector(t_data *data, t_player *player, float move_x, float move_y)
{
	int		speed;
	float	next_x;
	float	next_y;

	speed = 3;
	next_x = player->x + move_x * speed;
	next_y = player->y + move_y * speed;

	int radius = PLAYER_SIZE / 2;

	// if (!touch_wall(data, next_x + PLAYER_RADIUS, player->y)
	// 	&& !touch_wall(data, next_x - PLAYER_RADIUS, player->y))
	// 	player->x = next_x;

	// if (!touch_wall(data, player->x, next_y + PLAYER_RADIUS)
	// 	&& !touch_wall(data, player->x, next_y - PLAYER_RADIUS))
	// 	player->y = next_y;
	if (!touch_wall(data, next_x - radius, player->y - radius)
		&& !touch_wall(data, next_x + radius, player->y - radius)
		&& !touch_wall(data, next_x - radius, player->y + radius)
		&& !touch_wall(data, next_x + radius, player->y + radius))
		player->x = next_x;

	if (!touch_wall(data, player->x - radius, next_y - radius)
		&& !touch_wall(data, player->x + radius, next_y - radius)
		&& !touch_wall(data, player->x - radius, next_y + radius)
		&& !touch_wall(data, player->x + radius, next_y + radius))
		player->y = next_y;
	
	// if (!touch_wall(data, next_x + PLAYER_SIZE / 2, player->y)
	// && !touch_wall(data, next_x - PLAYER_SIZE / 2, player->y))
	// 	player->x = next_x;
	// if (!touch_wall(data, player->x, next_y + PLAYER_SIZE / 2)
	// && !touch_wall(data, player->x, next_y - PLAYER_SIZE / 2))
	// 	player->y = next_y;
}

void	move_player(t_data *data, t_player *player)
{
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;
	float move_x = 0;
	float move_y = 0;

	angle_speed = 0.03;
	if (player->rotate_left)
		player->angle -= angle_speed;
	if (player->rotate_right)
		player->angle += angle_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->forward)
	{
		move_x += cos_angle;
		move_y += sin_angle;
		//move_vector(data, player, cos_angle, sin_angle);
	}
	if (player->back)
	{
		move_x -= cos_angle;
		move_y -= sin_angle;
		//move_vector(data, player, -cos_angle, -sin_angle);
	}
	if (player->left)
	{
		move_x += sin_angle;
		move_y -= cos_angle;
		//move_vector(data, player, sin_angle, -cos_angle);
	}
	if (player->right)
	{
		move_x -= sin_angle;
		move_y += cos_angle;
		//move_vector(data, player, -sin_angle, cos_angle);
	}
	move_vector(data, player, move_x, move_y);
}
