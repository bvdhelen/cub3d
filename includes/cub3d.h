/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/05/04 20:07:15 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "aux/libft/libft.h"
# include "aux/gnl/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

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

// Definir el ancho y alto de la ventana
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Definir el tamaño de celda
#define TILE_SIZE 22

//estructura de imagen
typedef struct s_imagen
{
	void	*img;
	char	*addr; // img_pixels
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imagen;

typedef struct s_texture
{
	char	*path;
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

void 	free_all(t_data *data);

char	*skip_spaces(char *str);
int		parse_color(char *file, t_data *data);
int		parse_texture(char *file, t_data *data);
int		parse_elements(char *file, t_data *data);

int		parse_map(t_data *data, t_list *map_lines);

int		is_map_line(char *line);
int		parse_file(int fd, t_data *data);

t_data	*init_data(void);
int		init_window(t_data *data);
void	init_image(t_data *data);

int		handle_key(int key, t_data *data);
int		handle_event(t_data *data);

void	draw_map(t_data *data);
void	draw_square(t_data *data, int x, int y, int color);
void	put_pixel(t_data *data, int x, int y, int color);


#endif