/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/04/28 12:59:50 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//includes => NO AÑADIDOS EN EL GIT, los define generales tampoco
# include "aux/libft/libft.h"
# include "aux/gnl/get_next_line.h"

// Definir códigos de color
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define GREY		"\033[0;90m"
# define RESET		"\033[0m"

//estructura de imagen
typedef struct s_imagen
{
	void	*img;
	char	*addr; // img_pixels
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_imagen;

typedef struct s_texture
{
	void	*img;
	char	*addr; //text_pixels
	int		width;
	int		height;
}	t_texture;

typedef struct s_data
{
	void		*mlx_connection;
	void		*window;
	t_imagen	imagen; //primera struct

	//mapa
	char		**map;
	int			map_width;
	int			map_height;

	//techo y suelo
	int			floor_color[3];
	int			ceiling_color[3];
	
    //paredes
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;

    // Jugador: posición, dirección hacia donde mira, campo de visión
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}	t_data;

void	error_arg(void);
int		error(char *message);

#endif