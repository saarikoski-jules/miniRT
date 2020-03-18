#include "libft.h"
#include "error.h"
#include "rt.h"

int get_int(char *line, int *i)
{
	int val;

	if (ft_strchr("0123456789", (int)line[*i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	val = ft_atoi(line + *i);
	*i += ft_strmatch(line + *i, "0123456789");
	//error check
	return (val);
}

double get_float(char *line, int *i)
{
	double val;

	if (ft_strchr("0123456789", (int)line[*i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	val = ft_atof(line + *i);
	*i += ft_strmatch(line + *i, "0123456789");
	*i += ft_strmatch(line + *i, ".");
	*i += ft_strmatch(line + *i, "0123456789");
	//error check
	return (val);
}

void skip_comma(char *line, int *i)
{
	if (line[*i] == ',')
		(*i)++;
	else
		error_exit_msg(C_PARSE, E_PARSE);	
}

t_color *set_color(char *line, int *i)
{
	t_color *rgb;

	rgb = malloc(sizeof(t_color));
	rgb->r = get_int(line, i);
	skip_comma(line, i);
	rgb->g = get_int(line, i);
	skip_comma(line, i);
	rgb->b = get_int(line, i);
	return (rgb);
}
