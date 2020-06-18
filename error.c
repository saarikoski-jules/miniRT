/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:29:28 by jvisser       #+#    #+#                 */
/*   Updated: 2020/06/18 13:55:33 by jsaariko      ########   odam.nl         */
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
	ft_bzero(ptr, size);
	return (ptr);
}

void e_write(int fd, const char *buf, size_t size)
{
	int ret;

	if (fd <= 0) //is this correct?
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	ret = write(fd, buf, size);
	if (ret == -1)
		exit(errno);
}
