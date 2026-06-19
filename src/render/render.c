/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:35:58 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/19 22:53:47 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_info(t_data *data, t_ray *ray)
{
	float	hit_x;
	float	hit_y;

	// Calcular punto exacto de impacto (coordenadas dentro de la celda)
	if (ray->side == 0) // impacto vertical (Este u Oeste)
	{
		hit_y = data->player.y + ray->perp_wall_dist * ray->dir_y;
		ray->wall_x = hit_y - floor(hit_y);
		if (ray->dir_x > 0)
			ray->texture = &data->east;
		else
			ray->texture = &data->west;
	}
	else // impacto horizontal (Norte o Sur)
	{
		hit_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
		ray->wall_x = hit_x - floor(hit_x);
		if (ray->dir_y > 0)
			ray->texture = &data->south;
		else
			ray->texture = &data->north;
	}
	// Invertir wall_x para evitar espejado (según la dirección)
	if ((ray->side == 0 && ray->dir_x < 0) ||
		(ray->side == 1 && ray->dir_y > 0))
		ray->wall_x = 1.0f - ray->wall_x;
}

void	draw_2d(t_data *data)
{
	int	center_x;
	int	center_y;

	center_x = (int)(data->player.x * TILE_SIZE);
	center_y = (int)(data->player.y * TILE_SIZE);
	clear_image(data);
	draw_map(data);
	draw_player(data, data->player.x, data->player.y, 0xFFDA20);
	put_pixel(data, center_x, center_y, 0xFF0000);
	draw_all_rays_2d(data);
}

void	draw_3d(t_data *data, int x)
{
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;

	init_ray_direction(data, x, &ray);
	init_step_and_side(data, &ray);
	if (!dda_loop(data, &ray))
		return ;
	calc_perp_distance(&ray);
	get_wall_info(data, &ray);
	line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	draw_vertical_stripe(data, x, draw_start, draw_end, &ray);
}

int	draw_loop(t_data *data)
{
	int	i;

	if (frame_limit())
		return (0);
	move_player(data, &data->player);
	if (CUB2D)
		draw_2d(data);
	else
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			draw_3d(data, i);
			i++;
		}
	}
	mlx_put_image_to_window(data->mlx_connection, data->window,
		data->imagen.img, 0, 0);
	return (0);
}
