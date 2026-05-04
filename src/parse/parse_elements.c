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

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

// //convierte file en info eliminando todos los espacios
// char	*erase_spaces(char *file)
// {
// 	char	*info;
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	while (file[i])
// 	{
// 		if (file[i] != ' ')
// 			j++;
// 		i++;
// 	}
// 	info = malloc(sizeof(char) * (j + 1));
// 	if (!info)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (file[i])
// 	{
// 		if (file[i]!= ' ')
// 			info[j++] = file[i];
// 		i++;
// 	}
// 	info[j] = '\0';
// 	return (info);
// }

int	parse_color(char *file, t_data *data)
{
	char	**rgb;
	char	*info;
	char	type;
	int		i;

	info = skip_spaces(file + 1);
	type = file[0];
	i = 0;

	while (info[i])//control de errores:fuera !(' ', ',', 0-9)
	{
		if (!ft_isspace(info[i]) && info[i] != ',' && !(info[i] >= '0' && info[i] <= '9'))
			return (-1);
		i++;
	}

	rgb = ft_split(info, ',');//separar
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])//3 valores
	{
		ft_freedp(rgb);
		return (-1);
	}

	i = 0;
	while (rgb[i])//rango entre 0-255
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			ft_freedp(rgb);
			return (-1);
		}
		i++;
	}

	if (type == 'F')
	{
		data->floor_color[0] = ft_atoi(rgb[0]);
		data->floor_color[1] = ft_atoi(rgb[1]);
		data->floor_color[2] = ft_atoi(rgb[2]);
	}
	else if (type == 'C')
	{
		data->ceiling_color[0] = ft_atoi(rgb[0]);
		data->ceiling_color[1] = ft_atoi(rgb[1]);
		data->ceiling_color[2] = ft_atoi(rgb[2]);
	}
	ft_freedp(rgb);
	return (0);
}

int	parse_texture(char *file, t_data *data)
{
	char	*path;
	char	*info;
	char	type;
	int		i;

	info = skip_spaces(file + 2);
	type = file[0];//ya valido el siguiente caracter y el espacio fuera de esta funcion
	i = ft_strlen(info);

	if (i < 4 || ft_strncmp(info + i - 4, ".xpm", 4) != 0)
		return (-1);

	path = ft_strdup(info);//extraer path
	if (!path)//validar path
		return (-1);

	if (type == 'N')
	{
		if (data->north.path)
			return (free(path), -1);
		data->north.path = path;
	}
	else if (type == 'S')
	{
		if (data->south.path)
			return (free(path), -1);
		data->south.path = path;
	}
	else if (type == 'E')
	{
		if (data->east.path)
			return (free(path), -1);
		data->east.path = path;
	}
	else if (type == 'W')
	{
		if (data->west.path)
			return (free(path), -1);
		data->west.path = path;
	}
	return (0);
}

int	parse_elements(char *file, t_data *data)
{
	char	*start;

	start = skip_spaces(file);
	if (*start == '\0' || *start == '\n')//saltar líneas vacías
		return (0);
	if (ft_strncmp(start, "F ", 2) == 0 || ft_strncmp(start, "C ", 2) == 0)
	{
		// if (parse_color(start, data) == -1)
		// 	return (-1);
		return (parse_color(start, data));
	}
	else if (ft_strncmp(start, "NO ", 3) == 0 || ft_strncmp(start, "SO ", 3) == 0 || ft_strncmp(start, "EA ", 3) == 0 || ft_strncmp(start, "WE ", 3) == 0)
	{
		// if (parse_texture(start, data) == -1)
		// 	return (-1);
		return (parse_texture(start, data));
	}
	else//si es cualquier otra cosa error
		return (-1);//error

	//mapa no puede ser encontrado antes que todos los elementos
	//preguntar ¿si no define algun elemento sale por error o se le asigna uno default?
	// SALIR SI FALTA ALGUNO
}
