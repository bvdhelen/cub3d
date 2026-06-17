/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:35:58 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/17 19:28:35 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_2D(t_data *data)
{
    int center_x;
    int center_y;

	center_x = (int)(data->player.x * TILE_SIZE);
	center_y = (int)(data->player.y * TILE_SIZE);
    clear_image(data);
    draw_map(data);
    draw_player(data, data->player.x, data->player.y, 0xFFDA20);
    put_pixel(data, center_x, center_y, 0xFF0000);
    draw_all_rays_2d(data);
}

void draw_3D(t_data *data, int x)
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
	line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0)
		draw_start = 0;
    draw_end = line_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
    draw_vertical_stripe(data, x, draw_start, draw_end);
}

int	draw_loop(t_data *data)
{
	int	i;

	if (frame_limit()) //ketchup
		return (0);
	move_player(data, &data->player);
	if (CUB2D)
		draw_2D(data);
	else
	{
		i = 0;
		while(i < WIN_WIDTH)
		{
			draw_3D(data, i);
			i++;
		}
	}
	mlx_put_image_to_window(data->mlx_connection, data->window,
		data->imagen.img, 0, 0);
	return (0);
}
