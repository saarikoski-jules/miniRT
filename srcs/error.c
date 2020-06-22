/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:29:28 by jvisser       #+#    #+#                 */
/*   Updated: 2020/06/22 11:29:49 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

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

void	*e_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit_errno();
	ft_bzero(ptr, size);
	return (ptr);
}

void	e_write(int fd, const char *buf, size_t size)
{
	int ret;

	if (fd < 0)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	ret = write(fd, buf, size);
	if (ret == -1)
		exit(errno);
}
