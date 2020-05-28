/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:29:28 by jvisser       #+#    #+#                 */
/*   Updated: 2020/05/23 14:37:04 by jsaariko      ########   odam.nl         */
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
	{
		ft_printf("error: '%d'\n", line[i]);
		error_exit_msg(C_PARSE_INVALID_INT, E_PARSE_INVALID_INT);
	}
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

void	error_exit_msg(const unsigned int e_code, const char *e_msg)
{
	ft_printf("Error\n");
	ft_printf("MiniRT(%d): %s\n", e_code, e_msg);
	exit(e_code);
}

void	error_exit_errno(void)
{
	ft_printf("Error\n");
	ft_printf("MiniRT(%d): %s\n", errno, strerror(errno));
	exit(errno);
}

void *e_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit_errno();
	return (ptr);
}