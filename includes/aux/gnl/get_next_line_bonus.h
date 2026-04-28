/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvdhelen <bvdhelen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:46:51 by ptrapero          #+#    #+#             */
/*   Updated: 2026/04/28 13:38:27 by bvdhelen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# ifndef NUM_FD
#  define NUM_FD 1024
# endif

char	*ft_strchr(const char *s, int c);
//size_t	ft_strlen(const char *s);
char	*ft_strjoin_free(char *s1, char *s2);
//char	*ft_strdup(const char *s);
//char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
