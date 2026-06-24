/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:48:31 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/24 19:58:14 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1. init_ray_direction (calcula dir, plane, ray_dir y los mete en t_ray)
void	init_ray_direction(t_data *data, int x, t_ray *ray)
{
	float	camera_x;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;

	camera_x = 2 * x / (float)WIN_WIDTH - 1;
	dir_x = cos(data->player.angle);
	dir_y = sin(data->player.angle);
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
	ray->dir_x = dir_x + plane_x * camera_x;
	ray->dir_y = dir_y + plane_y * camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
}

// 2. init_step_and_side (calcula steps y side_dist iniciales)
void	init_step_and_side(t_data *data, t_ray *ray)
{
	ray->delta_dx = fabs(1.0 / ray->dir_x);
	ray->delta_dy = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (data->player.x - ray->map_x) * fabs(1.0 / ray->dir_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dx = (ray->map_x + 1.0 - data->player.x)
			* fabs(1.0 / ray->dir_x);
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (data->player.y - ray->map_y) * fabs(1.0 / ray->dir_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dy = (ray->map_y + 1.0 - data->player.y)
			* fabs(1.0 / ray->dir_y);
	}
}

// 3. dda_loop (realiza el bucle y devuelve 1 si impactó, 0 si salió del mapa)
// Comprobar límites
int	dda_loop(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map_width
			|| ray->map_y < 0 || ray->map_y >= data->map_height)
			return (0);
		if (data->map[ray->map_y][ray->map_x] == '1')
			return (1);
	}
}

// 4. calc_perp_distance (calcula perp_wall_dist, NO PRODUCE OJO DE PEZ)
void	calc_perp_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dx - ray->delta_dx);
	else
		ray->perp_wall_dist = (ray->side_dy - ray->delta_dy);
}

// 5. draw_vertical_line (dibuja techo, pared, suelo)
void	draw_vertical_line(t_data *data, t_wall *wall, t_ray *ray)
{
	t_texdraw	t;

	t.tex_x = (int)(ray->wall_x * (ray->texture->width - 1));
	if (t.tex_x < 0)
		t.tex_x = 0;
	if (t.tex_x >= ray->texture->width)
		t.tex_x = ray->texture->width - 1;
	t.step = (float)ray->texture->height / wall->line_height;
	t.tex_pos = (wall->start - wall->real_start) * t.step;
	t.y = 0;
	while (t.y < wall->start)
		put_pixel(data, wall->x, t.y++, data->ceiling_color);
	while (t.y < wall->end)
	{
		t.tex_y = (int)t.tex_pos;
		if (t.tex_y >= ray->texture->height)
			t.tex_y = ray->texture->height - 1;
		t.color = *(int *)(ray->texture->addr
				+ (t.tex_y * ray->texture->line_len + t.tex_x
					* (ray->texture->bpp / 8)));
		put_pixel(data, wall->x, t.y++, t.color);
		t.tex_pos += t.step;
	}
	while (t.y < WIN_HEIGHT)
		put_pixel(data, wall->x, t.y++, data->floor_color);
}
