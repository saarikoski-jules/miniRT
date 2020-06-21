/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_number.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 18:13:38 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 18:24:55 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "error.h"
#include <limits.h>

int			get_int(char *line, size_t *i)
{
	long long val;

	*i += ft_strmatch(line + *i, " ");
	validate_int(line + *i);
	val = ft_atoll(line + *i);
	if (ft_strchr("-+", (int)line[*i]) != NULL)
		(*i)++;
	*i += ft_strmatch(line + *i, "0123456789");
	if (val > INT_MAX || val < INT_MIN)
		error_exit_msg(C_PARSE_INVALID_INT, E_PARSE_INVALID_INT);
	return ((int)val);
}

double		get_float(char *line, size_t *i)
{
	double val;

	*i += ft_strmatch(line + *i, " ");
	validate_float(line + *i);
	val = ft_atof(line + *i);
	if (ft_strchr("+-", line[(*i)]))
		(*i)++;
	if (line[(*i)] == '.')
		(*i)++;
	*i += ft_strmatch(line + *i, "0123456789");
	*i += ft_strmatch(line + *i, ".");
	*i += ft_strmatch(line + *i, "0123456789");
	return (val);
}
