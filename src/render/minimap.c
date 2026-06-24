/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:09:59 by ptrapero          #+#    #+#             */
/*   Updated: 2026/06/24 16:28:49 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minisquare(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_miniplayer(t_data *data, int color)
{
	int	x;
	int	y;

	x = MINIMAP_X + data->player.x * MINIMAP_SCALE;
	y = MINIMAP_Y + data->player.y * MINIMAP_SCALE;
	put_pixel(data, x, y, color);
	put_pixel(data, x + 1, y, color);
	put_pixel(data, x - 1, y, color);
	put_pixel(data, x, y + 1, color);
	put_pixel(data, x, y - 1, color);
}

void	draw_single_miniray(t_data *data, float dir_x, float dir_y)
{
	float	ray_x;
	float	ray_y;
	int		sx;
	int		sy;

	ray_x = data->player.x;
	ray_y = data->player.y;
	while (!touch_wall(data, ray_x, ray_y))
	{
		sx = MINIMAP_X + ray_x * MINIMAP_SCALE;
		sy = MINIMAP_Y + ray_y * MINIMAP_SCALE;
		put_pixel(data, sx, sy, 0xFFFF00);
		ray_x += dir_x * 0.05f;
		ray_y += dir_y * 0.05f;
	}
}

void	draw_minirays(t_data *data)
{
	float	cos_angle;
	float	sin_angle;
	float	plane_x;
	float	plane_y;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		x;

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
		draw_single_miniray(data, ray_dir_x, ray_dir_y);
		x += 20;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_minisquare(data,
					MINIMAP_X + x * MINIMAP_SCALE,
					MINIMAP_Y + y * MINIMAP_SCALE,
					0xFFAACC);
			x++;
		}
		y++;
	}
	draw_minirays(data);
	draw_miniplayer(data, 0xFF7700);
}
