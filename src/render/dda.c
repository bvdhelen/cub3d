/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:48:31 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/20 17:29:16 by bvdhelen         ###   ########.fr       */
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
	float	delta_x;
	float	delta_y;

	delta_x = fabs(1.0 / ray->dir_x);
	delta_y = fabs(1.0 / ray->dir_y);
	ray->delta_dist_x = delta_x;
	ray->delta_dist_y = delta_y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x) * delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y) * delta_y;
	}
}

// 3. dda_loop (realiza el bucle y devuelve 1 si impactó, 0 si salió del mapa)
// Comprobar límites
int	dda_loop(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
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
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

// 5. draw_vertical_line (dibuja techo, pared, suelo)
// Calcular columna en la textura
// Paso vertical (avance en la textura por cada píxel de la pared)
void	draw_vertical_line(t_data *data, int x, int start, int end, t_ray *ray)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;

	tex_x = (int)(ray->wall_x * (ray->texture->width - 1));
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	step = (float)ray->texture->height / (float)(end - start);
	tex_pos = 0.0f;
	y = 0;
	while (y < start)
		put_pixel(data, x, y++, data->ceiling_color);
	while (y < end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= ray->texture->height)
			tex_y = ray->texture->height - 1;
		color = *(int *)(ray->texture->addr
				+ (tex_y * ray->texture->line_len + tex_x
					* (ray->texture->bpp / 8)));
		put_pixel(data, x, y++, color);
		tex_pos += step;
	}
	while (y < WIN_HEIGHT)
		put_pixel(data, x, y++, data->floor_color);
}
