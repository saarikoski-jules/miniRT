/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:37:18 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 15:34:47 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "error.h"
#include "libft.h"
#include "parse.h"

t_vec	*get_vec(char *line, size_t *i)
{
	t_vec	*vec;

	vec = (t_vec*)ft_calloc(1, sizeof(t_vec));
	if (vec == NULL)
		error_exit_errno();
	(*i) += ft_strmatch(&line[*i], " ");
	vec->x = get_float(line, i);
	skip_comma(line, i);
	vec->y = get_float(line, i);
	skip_comma(line, i);
	vec->z = get_float(line, i);
	return (vec);
}
