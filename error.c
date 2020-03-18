/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:29:28 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 14:09:25 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"
#include "error.h"

void	validate_int(char *line)
{
	int i;

	i = 0;
	if (ft_strchr("-+", (int)line[i]) != NULL)
		i++;
	if (ft_strchr("0123456789", (int)line[i]) == NULL)
		error_exit_msg(C_PARSE_INVALID_INT, E_PARSE_INVALID_INT);
}

void	validate_float(char *line)
{
	int i;

	i = 0;
	if (ft_strchr("-+", (int)line[i]) != NULL)
		i++;
	if ((int)line[i] == '.')
		i++;
	if (ft_strchr("0123456789", (int)line[i]) == NULL)
		error_exit_msg(C_PARSE_INVALID_FLOAT, E_PARSE_INVALID_FLOAT);
}

void	error_exit_errno(void)
{
	ft_printf("Error\n");
	ft_printf("MiniRT(%d): %s\n", errno, strerror(errno));
	exit(errno);
}

void	error_exit_msg(const unsigned int e_code, const char *e_msg)
{
	ft_printf("Error\n");
	ft_printf("MiniRT(%d): %s\n", e_code, e_msg);
	exit(e_code);
}
