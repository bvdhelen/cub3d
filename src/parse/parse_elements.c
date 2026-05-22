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

void	printvalues(t_data *data)
{
	if (data->north.addr)
		printf("%s\n", data->north.addr);
	if (data->south.addr) //va mal
		printf("%s\n", data->south.addr);
	if (data->east.addr) //va mal
		printf("%s\n", data->east.addr);
	if (data->west.addr)
		printf("%s\n", data->west.addr);
	printf("rgbf %i %i %i\n", data->floor_color[0],
		data->floor_color[1], data->floor_color[2]);
	printf("rgbc %i %i %i\n", data->ceiling_color[0],
		data->floor_color[1], data->floor_color[2]);
}

void	charnull_gnl(char *s)//revisar nombre
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	s[i] = '\0';
}

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

int	overflow(char *s)
{
	int	overflow;

	overflow = 0;
	ft_atoi_overflow(s, &overflow);
	return (overflow);
}

int	ketchup(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (-1);
}

int	parse_color(char *file, t_data *data)
{
	char	**rgb;
	char	*info;
	char	type;
	int		i;
	int		comma;

	info = skip_spaces(file + 1);
	//charnull_gnl(info);
	type = file[0];
	i = 0;
	comma = 0;
	while (info[i]) //control de errores:fuera !(' ', ',', 0-9)
	{
		if (!ft_isspace(info[i]) && info[i] != ','
			&& !(info[i] >= '0' && info[i] <= '9'))
			return (-1);
		if (info[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (-1);
	rgb = ft_split(info, ','); //separar
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3]) //3 valores
	{
		ft_freedp(rgb);
		return (-1);
	}
	//printf("rgb 0-> '%s'\n", rgb[0]);
	//printf("rgb 1-> '%s'\n", rgb[1]);
	//printf("rgb 2-> '%s'\n", rgb[2]);
	i = 0;
	while (rgb[i]) //rango entre 0-255
	{
		if (overflow(rgb[i]) || ketchup(rgb[i])
			|| ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			ft_freedp(rgb);
			return (-1);
		}
		i++;
	}
	if (type == 'F')
	{
		if (data->floor_set == 1)
			return (ft_freedp(rgb), -1);
		data->floor_color[0] = ft_atoi(rgb[0]);
		data->floor_color[1] = ft_atoi(rgb[1]);
		data->floor_color[2] = ft_atoi(rgb[2]);
		data->floor_set = 1;
		printf("rgbF-> %i %i %i\n", data->floor_color[0],
			data->floor_color[1], data->floor_color[2]);
	}
	else if (type == 'C')
	{
		if (data->ceiling_set == 1)
			return (ft_freedp(rgb), -1);
		data->ceiling_color[0] = ft_atoi(rgb[0]);
		data->ceiling_color[1] = ft_atoi(rgb[1]);
		data->ceiling_color[2] = ft_atoi(rgb[2]);
		data->ceiling_set = 1;
		printf("rgbC-> %i %i %i\n", data->ceiling_color[0],
			data->ceiling_color[1], data->ceiling_color[2]);
	}
	ft_freedp(rgb);
	//printvalues(data);
	return (0);
}

int	parse_texture(char *file, t_data *data)
{
	char	*path;
	char	*info;
	char	type;
	int		i;

	info = skip_spaces(file + 2);
	//charnull_gnl(info);
	type = file[0];
	//ya valido el siguiente caracter y el espacio fuera de esta funcion
	i = ft_strlen(info);
	while (ft_isspace(info[i - 1]))
		i--;
	if (i < 4 || ft_strncmp(info + i - 4, ".xpm", 4) != 0)
		return (-1);
	path = ft_strdup(info); //extraer path
	if (!path) //validar path ????? LIBERAR PATH
		return (-1);
	printf("type-> %c\n", type);
	if (type == 'N')
	{
		if (data->north.addr)
			return (free(path), -1);
		data->north.addr = path;
		data->north_set = 1;
	}
	else if (type == 'S')
	{
		if (data->south.addr)
			return (free(path), -1);
		data->south.addr = path;
		data->south_set = 1;
	}
	else if (type == 'E')
	{
		if (data->east.addr)
			return (free(path), -1);
		data->east.addr = path;
		data->east_set = 1;
	}
	else if (type == 'W')
	{
		if (data->west.addr)
			return (free(path), -1);
		data->west.addr = path;
		data->west_set = 1;
	}
	return (0);
}

int	parse_elements(char *file, t_data *data)
{
	char	*info;

	info = skip_spaces(file);
	if (*info == '\0' || *info == '\n') //saltar líneas vacías
		return (0);
	if ((*info == 'F' || *info == 'C') && ft_isspace(info[1]))
	// ft_strncmp(info, "F ", 2) == 0 || ft_strncmp(info, "C ", 2) == 0)
		return (parse_color(info, data));
	else if ((ft_strncmp(info, "NO", 2) == 0 || ft_strncmp(info, "SO", 2) == 0
			|| ft_strncmp(info, "EA", 2) == 0 || ft_strncmp(info, "WE", 2) == 0)
		&& ft_isspace(info[2]))
	//(ft_strncmp(info, "NO ", 3) == 0 || ft_strncmp(info, "SO ", 3) == 0
		//|| ft_strncmp(info, "EA ", 3) == 0 || ft_strncmp(info, "WE ", 3) == 0)
		return (parse_texture(info, data));
	else//si es cualquier otra cosa error
		return (-1);//error
	//mapa no puede ser encontrado antes que todos los elementos
	//preguntar ¿si no define algun elemento sale por error 
		//o se le asigna uno default?
	// SALIR SI FALTA ALGUNO
}
