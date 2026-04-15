/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/04/08 20:05:33 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//includes => NO AÑADIDOS EN EL GIT, los define generales tampoco
# include "../src/aux/libft/libft.h"
# include "../src/aux/gnl/get_next_line.h"

//estructura de imagen
typedef struct s_imagen
{
	void	*img;
	char	*addr; // img_pixels
	int		bits per_pixel;
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
	t_img		imagen; //primera struct

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

#endif
