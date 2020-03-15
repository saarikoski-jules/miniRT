/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:29:28 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/15 18:44:35 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

void	error_exit_msg(const unsigned int e_code, const char *e_msg)
{
	ft_printf("Error\n");
	ft_printf("MiniRT(%d): %s\n", e_code, e_msg);
	exit(e_code);
}
