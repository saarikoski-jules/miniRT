/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 18:09:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 11:32:21 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "parse.h"
#include <limits.h>

void			skip_comma(char *line, size_t *i)
{
	if (line[*i] == ',')
		(*i)++;
	else
		error_exit_msg(C_PARSE_NO_COMMA, E_PARSE_NO_COMMA);
	if (line[*i] == ' ')
		error_exit_msg(C_PARSE_NO_COMMA, E_PARSE_NO_COMMA);
}

unsigned char	validate_color(char *line, size_t *i)
{
	int val;

	val = get_int(line, i);
	if (val < 0 || val > 255)
		error_exit_msg(C_INVALID_COLOR, E_INVALID_COLOR);
	return ((unsigned char)val);
}

t_color			*get_color(char *line, size_t *i)
{
	t_color *color;

	*i += ft_strmatch(line + *i, " ");
	color = (t_color *)e_malloc(sizeof(t_color));
	color->r = validate_color(line, i);
	skip_comma(line, i);
	color->g = validate_color(line, i);
	skip_comma(line, i);
	color->b = validate_color(line, i);
	return (color);
}

t_vec			*get_vec(char *line, size_t *i)
{
	t_vec	*vec;

	vec = (t_vec*)e_malloc(sizeof(t_vec));
	(*i) += ft_strmatch(&line[*i], " ");
	vec->x = get_float(line, i);
	skip_comma(line, i);
	vec->y = get_float(line, i);
	skip_comma(line, i);
	vec->z = get_float(line, i);
	return (vec);
}
