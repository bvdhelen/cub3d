/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/06/24 13:12:45 by ptrapero         ###   ########.fr       */
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
# include <math.h>
# include <sys/time.h>

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
# define WIN_WIDTH 1800//1920 //1500 //1920
# define WIN_HEIGHT 1000//1080 //800 //1080

//minimap
#define MINIMAP_X 20
#define MINIMAP_Y 20
#define MINIMAP_SCALE 8

// Definir el tamaño de celda y de jugador
# define TILE_SIZE 22
# define PLAYER_SIZE 7
# define PLAYER_RADIUS_CELL 0.45f

// Velocidades del jugador
# define MOVE_SPEED   0.12f   // CELDAS por frame
# define ROTATE_SPEED  0.05f  // radianes por frame

// pi y campo de visión (field of view) de 60°, FOV es pi/3
# define PI 3.141592653589793
# define FOV 1.0471975511965976

// TRUE para ver en 2D; FALSE para ver en 3D
# define CUB2D 0

typedef struct s_flood
{
	char	**map;
	int		w;
	int		h;
}	t_flood;

typedef struct s_imagen
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imagen;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	int		forward;
	int		back;
	int		left;
	int		right;

	int		rotate_left;
	int		rotate_right;
}	t_player;

typedef struct s_data
{
	void		*mlx_connection;
	void		*window;
	t_imagen	imagen;

	//mapa
	char		**map;
	int			map_width;
	int			map_height;

	//techo y suelo
	int			floor_rgb[3];
	int			floor_color;
	int			ceiling_rgb[3];
	int			ceiling_color;

	//paredes
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;

	//estado set
	int			floor_set;
	int			ceiling_set;
	int			north_set;
	int			south_set;
	int			east_set;
	int			west_set;

	int			fd;
	//jugador
	t_player	player;

}	t_data;

//DDA
typedef struct s_ray
{
	float		dir_x;
	float		dir_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	float		perp_wall_dist;
	float		wall_x; // coordenada horizontal dentro de la textura (0..1)
	t_texture	*texture; // puntero a la textura a usar
}	t_ray;

//init
t_data	*init_data(void);
int		init_fd(char **argv, t_data *data);
int		init_window(t_data *data);
void	init_image(t_data *data);

//hooks
void	hooks(t_data *data);

//parse
int		parse_color1(char *file, t_data *data);
int		rgb_to_hex(int *rgb);
int		parse_elements(char *file, t_data *data);

int		build_map_from_list(t_data *data, t_list *map_lines);
int		invalid_chars(t_data *data);
int		count_player(t_data *data, int *px, int *py);
int		parse_map(t_data *data, t_list *map_lines);

int		parse_file(t_data *data);

//utils
int		error(char *message);
void	error_arg(void);

void	free_all(t_data *data);

void	charnull_gnl(char *s);
void	clean_gnl(int fd);
char	*skip_spaces(char *str);
float	get_distance(float x, float y);
void	check_parse(t_data *data);

//render
void	put_pixel(t_data *data, int x, int y, int color);
int		frame_limit(void);

void	clear_image(t_data *data);
void	draw_player(t_data *data, float x, float y, int color);
void	draw_square(t_data *data, int x, int y, int color);
void	draw_map(t_data *data);
int		touch_wall(t_data *data, float pos_x, float pos_y);
void	move_player(t_data *data, t_player *player);

void	draw_wall(t_data *data, int x);
int		draw_loop(t_data *data);

void	draw_all_rays_2d(t_data *data);
int		load_textures(t_data *data);

//minimap
void	draw_minimap(t_data *data);

//dda
void	init_ray_direction(t_data *data, int x, t_ray *ray);
void	init_step_and_side(t_data *data, t_ray *ray);
int		dda_loop(t_data *data, t_ray *ray);
void	calc_perp_distance(t_ray *ray);
//void	draw_vertical_line(t_data *data, int x, int start, int end, t_ray *ray);
void	draw_vertical_line(t_data *data, int x, int start, int end, t_ray *ray, int line_height, int real_start);

void	get_wall_info(t_data *data, t_ray *ray);

#endif