/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:37:04 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/11 19:32:41 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	pixel = data->imagen.addr
		+ (y * data->imagen.line_length
			+ x * (data->imagen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

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

void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int j;

	i = -1;
	j = (PLAYER_SIZE / -2);
	while (i++ < PLAYER_SIZE)
		put_pixel(data, x + i + j, y + j, color);
	i = -1;
	while (i++ < PLAYER_SIZE)
		put_pixel(data, x + j, y + i + j, color);
	i = -1;
	while (i++ < PLAYER_SIZE)
		put_pixel(data, x + PLAYER_SIZE + j, y + i + j, color);
	i = -1;
	while (i++ < PLAYER_SIZE)
		put_pixel(data, x + i + j, y + PLAYER_SIZE + j, color);
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

void	draw_mapaa(t_data *data)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = data->map;
	color = 0xFF0099;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}
