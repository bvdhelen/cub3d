/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 22:09:39 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/06/19 23:16:59 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one_texture(t_data *data, t_texture *tex, char *side)
{
	tex->img = mlx_xpm_file_to_image(data->mlx_connection, tex->path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		error("Failed to load texture ");
		ft_putstr_fd(side, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

int	load_textures(t_data *data)
{
	if (load_one_texture(data, &data->north, "NO") == -1)
		return (-1);
	if (load_one_texture(data, &data->south, "SO") == -1)
		return (-1);
	if (load_one_texture(data, &data->east, "EA") == -1)
		return (-1);
	if (load_one_texture(data, &data->west, "WE") == -1)
		return (-1);
	return (0);
}
