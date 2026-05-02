/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:24:26 by bvdhelen          #+#    #+#             */
/*   Updated: 2026/05/02 13:24:26 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Función de error principal*/
int	error(char *message)
{
	ft_putstr_fd(RED "Error: \n" RESET, 2);
	ft_putstr_fd(message, 2);
	//exit(EXIT_FAILURE);
	return (-1);
}

/*Función error de argumentos*/
void	error_arg(void)
{
	ft_putstr_fd(MAGENTA "Error: invalid number of arguments\n" RESET, 2);
	ft_putstr_fd("Usage:\t ./cub3d ....\n", 2);
}
