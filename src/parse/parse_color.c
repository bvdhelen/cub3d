/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:41:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/12 18:03:52 by bvdhelen         ###   ########.fr       */
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
		if (!ft_isdigit(s[i]))
			return (error("invalid element: not a digit\n"));
		i++;
	}
	return (0);
}

int	set_color(char **rgb, t_data *data, char type)
{
	if (type == 'F')
	{
		if (data->floor_set == 1)
			return (ft_freedp(rgb), -1);
		data->floor_rgb[0] = ft_atoi(rgb[0]);
		data->floor_rgb[1] = ft_atoi(rgb[1]);
		data->floor_rgb[2] = ft_atoi(rgb[2]);
		data->floor_set = 1;
	}
	else if (type == 'C')
	{
		if (data->ceiling_set == 1)
			return (ft_freedp(rgb), -1);
		data->ceiling_rgb[0] = ft_atoi(rgb[0]);
		data->ceiling_rgb[1] = ft_atoi(rgb[1]);
		data->ceiling_rgb[2] = ft_atoi(rgb[2]);
		data->ceiling_set = 1;
	}
	return (0);
}

int	parse_color2(char *info, char type, t_data *data)
{
	int		i;
	char	**rgb;
	char	*trimmed; //y esto

	rgb = ft_split(info, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_freedp(rgb), error("invalid element: wrong format RGB\n"));
	i = 0;
	while (rgb[i])
	{
		//ketchup -> he añadido esto porque no iba con espacios
		trimmed = skip_spaces(rgb[i]);
		if (overflow_n_checknum(trimmed))
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
