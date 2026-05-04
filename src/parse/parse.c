/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:53:10 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/04 19:38:50 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '1' || line[i] == '0');
}

static void	clean_gnl(int fd)
{
	char *tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

int	parse_file(int fd, t_data *data)
{
	char	*file;
	int		map_started;
	t_list	*map_lines;
	int		result;

	map_started = 0;
	map_lines = NULL;
	file = get_next_line(fd);
	while (file)
	{
		if (!map_started)
		{
			if (is_map_line(file))
				map_started = 1;
			else if (parse_elements(file, data) == -1)
            {
                free(file);
				clean_gnl(fd);
				return (error("Invalid element\n"));
            }
			if (!map_started)
			{
				free(file);
				file = get_next_line(fd);
				continue;
			}
		}
		ft_lstadd_back(&map_lines, ft_lstnew(file));
		file = get_next_line(fd);
	}
	if (!map_started)
		return (error("No map found\n"));
	result = parse_map(data, map_lines);
	ft_lstclear(&map_lines, free);
	if (result == -1)
		return (-1);
	return (0);
}
