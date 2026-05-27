/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:05:52 by ptrapero          #+#    #+#             */
/*   Updated: 2026/03/16 21:05:52 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	overflow_n_checknum(char *s)
{
	int	overflow;
	int	i;

	overflow = 0;
	ft_atoi_overflow(s, &overflow);
	if (overflow)
		return (error("invalid element: overflow\n"));
	if (ft_atoi(s) < 0 || ft_atoi(s) > 255)
		return (error("invalid element: number not allowed\n"));
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (error("invalid element: missing number\n"));
}

int	set_color(char **rgb, t_data *data, char type)
{
	if (type == 'F')
	{
		if (data->floor_set == 1)
			return (ft_freedp(rgb), -1);
		data->floor_color[0] = ft_atoi(rgb[0]);
		data->floor_color[1] = ft_atoi(rgb[1]);
		data->floor_color[2] = ft_atoi(rgb[2]);
		data->floor_set = 1;
	}
	else if (type == 'C')
	{
		if (data->ceiling_set == 1)
			return (ft_freedp(rgb), -1);
		data->ceiling_color[0] = ft_atoi(rgb[0]);
		data->ceiling_color[1] = ft_atoi(rgb[1]);
		data->ceiling_color[2] = ft_atoi(rgb[2]);
		data->ceiling_set = 1;
	}
	return (0);
}

int	parse_color2(char *info, char type, t_data *data)
{
	char	**rgb;
	int		i;

	rgb = ft_split(info, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_freedp(rgb), error("invalid element: wrong format RGB\n"));
	i = 0;
	while (rgb[i])
	{
		if (overflow_n_checknum(rgb[i]))
			return (ft_freedp(rgb), -1);
		i++;
	}
	if (set_color(rgb, data, type))
		return (error("invalid element: duplicate color\n"));
	ft_freedp(rgb);
	return (0);
}

int	parse_color1(char *file, t_data *data)
{
	char	*info;
	char	type;
	int		i;
	int		comma;

	info = skip_spaces(file + 1);
	type = file[0];
	i = 0;
	comma = 0;
	while (info[i])
	{
		if (!ft_isspace(info[i]) && info[i] != ',' && !ft_isdigit(info[i]))
			return (error("invalid element: char not allowed\n"));
		if (info[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (error("invalid element: wrong format RGB\n"));
	if (parse_color2(info, type, data))
		return (-1);
	return (0);
}

int	set_texture(char *path, char **addr, int *set)
{
	if (*addr)
		return (free(path), error("invalid element: duplicate texture\n"));
	*addr = path;
	*set = 1;
	return (0);
}

int	parse_texture(char *file, t_data *data)
{
	char	*path;
	char	*info;
	char	type;
	int		i;

	info = skip_spaces(file + 2);
	type = file[0];
	i = ft_strlen(info);
	while (ft_isspace(info[i - 1]))
		i--;
	if (i < 4 || ft_strncmp(info + i - 4, ".xpm", 4) != 0)
		return (error("invalid element: invalid texture\n"));
	//path = ft_strdup(info);
	path = ft_substr(info, 0, i);
	if (!path)
		return (error("invalid element: invalid texture\n"));
	if (type == 'N')
		return (set_texture(path, &data->north.addr, &data->north_set));
	else if (type == 'S')
		return (set_texture(path, &data->south.addr, &data->south_set));
	else if (type == 'E')
		return (set_texture(path, &data->east.addr, &data->east_set));
	else if (type == 'W')
		return (set_texture(path, &data->west.addr, &data->west_set));
	return (0);
}

int	parse_elements(char *file, t_data *data)
{
	char	*info;

	info = skip_spaces(file);
	if (*info == '\0' || *info == '\n')
		return (0);
	if ((*info == 'F' || *info == 'C') && ft_isspace(info[1]))
		return (parse_color1(info, data));
	else if ((ft_strncmp(info, "NO", 2) == 0 || ft_strncmp(info, "SO", 2) == 0
			|| ft_strncmp(info, "EA", 2) == 0 || ft_strncmp(info, "WE", 2) == 0)
		&& ft_isspace(info[2]))
		return (parse_texture(info, data));
	else
		return (-1);
}
