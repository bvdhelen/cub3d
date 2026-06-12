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

int	set_texture(char *path, char **dest_path, int *set)
{
	if (*dest_path)
		return (free(path), error("invalid element: duplicate texture\n"));
	*dest_path = path;
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
	path = ft_substr(info, 0, i);
	if (!path)
		return (error("invalid element: invalid texture\n"));
	if (type == 'N')
		return (set_texture(path, &data->north.path, &data->north_set));
	else if (type == 'S')
		return (set_texture(path, &data->south.path, &data->south_set));
	else if (type == 'E')
		return (set_texture(path, &data->east.path, &data->east_set));
	else if (type == 'W')
		return (set_texture(path, &data->west.path, &data->west_set));
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
