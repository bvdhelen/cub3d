#include "cub3d.h"

/*Función de error principal*/
int	error(char *message)
{
	ft_putstr_fd(RED "Error: \n" RESET, 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

/*Función error de argumentos*/
void	error_arg(void)
{
	ft_putstr_fd(MAGENTA "Error: invalid number of arguments\n" RESET, 2);
	ft_putstr_fd("Usage:\t ./cub3d ....\n", 2);
}
