#include "libft.h"
#include "error.h"
#include "rt.h"
#include "parse.h"
#include <limits.h>
#include <stdio.h>//

int get_int(char *line, size_t *i)
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
	//error check
	return ((int)val);
}

double get_float(char *line, size_t *i)
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
	// ft_printf("'%s'\ni: %d\nline from i: '%s'\nfloat: %f\n\n", line, *i, line + *i, val);
	// ft_printf("get_flt: %d\n", *i);
	//error check
	return (val);
}

void skip_comma(char *line, size_t *i)
{
	// ft_printf("in skip comma: line: '%s', i %d\n", line + *i, *i);
	if (line[*i] == ',')
		(*i)++;
	else
		error_exit_msg(C_PARSE_NO_COMMA, E_PARSE_NO_COMMA);
	if (line[*i] == ' ')
		error_exit_msg(C_PARSE_NO_COMMA, E_PARSE_NO_COMMA);
}

unsigned char validate_color(char *line, size_t *i)
{
	int val;

	val = get_int(line, i);
	if (val < 0 || val > 255)
		error_exit_msg(C_INVALID_COLOR, E_INVALID_COLOR);
	return ((unsigned char)val);
}

t_color *get_color(char *line, size_t *i)
{
	t_color *color;

	*i += ft_strmatch(line + *i, " ");
	color = (t_color*)malloc(sizeof(t_color));
	color->r = validate_color(line, i);
	skip_comma(line, i);
	color->g = validate_color(line, i);
	skip_comma(line, i);
	color->b = validate_color(line, i);
	return (color);
}

t_vec	*get_vec(char *line, size_t *i)
{
	t_vec	*vec;

	// ft_printf("getting the shit out of this vec '%s', %d\n", line, *i);
	vec = (t_vec*)ft_calloc(1, sizeof(t_vec));
	if (vec == NULL)
		error_exit_errno();
	(*i) += ft_strmatch(&line[*i], " ");
	// ft_printf("*i: %d\n", *i);
	vec->x = get_float(line, i);
	skip_comma(line, i);
	vec->y = get_float(line, i);
	skip_comma(line, i);
	vec->z = get_float(line, i);
	// ft_printf("x: %f\ny: %f\nz: %f\n", vec->x, vec->y, vec->z);
	return (vec);
}
