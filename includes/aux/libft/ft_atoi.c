/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:04:16 by ptrapero          #+#    #+#             */
/*   Updated: 2026/05/20 17:28:44 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	j;

	i = 0;
	sign = 1;
	j = 0;
	while (nptr[i] == 9 || nptr[i] == 10 || nptr[i] == 11 || nptr[i] == 12
		|| nptr[i] == 13 || nptr[i] == 32)
		i++;
	if ((nptr[i] == 45) || (nptr[i] == 43))
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		j = (10 * j) + (nptr[i] - 48);
		i++;
	}
	return (j * sign);
}

int	ft_atoi_overflow(const char *nptr, int *overflow)
{
	int		i;
	int		sign;
	long	j;

	i = 0;
	sign = 1;
	j = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if ((nptr[i] == 45) || (nptr[i] == 43))
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		j = (10 * j) + (nptr[i] - 48);
		if ((j > 2147483647 && sign == 1) || (j > 2147483648))
			*overflow = 1;
		i++;
	}
	return (j * sign);
}

/*int	main(void)
{
	char	e[] = "9999999";
	printf("%d",ft_atoi(e));
	return (0);
}*/