#include "libft.h"
#include "error.h"
#include "rt.h"
#include "parse.h"

int get_int(char *line, size_t *i)
{
	int val;

	*i += ft_strmatch(line + *i, " ");
	validate_int(line + *i);
	val = ft_atoi(line + *i);
	if (ft_strchr("-+", (int)line[*i]) != NULL)
		(*i)++;
	*i += ft_strmatch(line + *i, "0123456789");
	//error check
	return (val);
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
	// ft_printf("line: '%s', i %d\n", line, *i);
	if (line[*i] == ',')
		(*i)++;
	else
		error_exit_msg(C_PARSE_NO_COMMA, E_PARSE_NO_COMMA);	
}

t_color *get_color(char *line, size_t *i)
{
	t_color *color;

	// ft_printf("get_color: %d, '%s'\n", *i, line + *i);
	*i += ft_strmatch(line + *i, " ");
	color = (t_color*)malloc(sizeof(t_color));
	color->r = get_int(line, i);
	skip_comma(line, i);
	color->g = get_int(line, i);
	skip_comma(line, i);
	color->b = get_int(line, i);
	validate_color(color);
	return (color);
}
