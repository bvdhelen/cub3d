/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2026/03/09 17:54:05 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// MAPA ¿t_map?
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	char		**map;
	int			map_width;
	int			map_height;

	int			floor_color;
	int			ceiling_color;

	t_img		screen;
    
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;

    // ¿t_player?
    // Jugador: posición, dirección hacia donde mira, campo de visión
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}	t_game;
