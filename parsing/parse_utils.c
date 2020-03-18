#include "libft.h"
#include "error.h"
#include "rt.h"

int get_int(char *line, size_t *i)
{
	int val;

	if (ft_strchr("0123456789", (int)line[*i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	val = ft_atoi(line + *i);
	*i += ft_strmatch(line + *i, "0123456789");
	//error check
	return (val);
}

double get_float(char *line, size_t *i)
{
	double val;

	if (ft_strchr("0123456789-+", (int)line[*i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	val = ft_atof(line + *i);
	*i += ft_strmatch(line + *i, "0123456789-+");
	*i += ft_strmatch(line + *i, ".");
	*i += ft_strmatch(line + *i, "0123456789");
	//error check
	return (val);
}

void skip_comma(char *line, size_t *i)
{
	if (line[*i] == ',')
		(*i)++;
	else
		error_exit_msg(C_PARSE, E_PARSE);	
}

void set_color(char *line, size_t *i, t_color *rgb)
{
	rgb->r = get_int(line, i);
	skip_comma(line, i);
	rgb->g = get_int(line, i);
	skip_comma(line, i);
	rgb->b = get_int(line, i);
}
