/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 16:02:26 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/15 17:54:07 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

void get_resolution(char *line)
{
	t_resolution *res;
	int i;

	res = malloc(sizeof(t_resolution));
	i = ft_strmatch(line, " ");
	if (ft_strchr("0123456789", line[i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	res->res_x = ft_atoi(line + i);
	i += ft_strmatch(line + i, "0123456798");
	i += ft_strmatch(line + i, " ");
	if (ft_strchr("0123456789", line[i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	res->res_y = ft_atoi(line + i);
	ft_printf("res_x %d, rez_y %d\n", res->res_x, res->res_y);
}

int get_int(char *line, int *i)
{
	int val;

	if (ft_strchr("0123456789", (int)line[*i]) == NULL)
		error_exit_msg(C_PARSE, E_PARSE);
	val = ft_atoi(line + *i);
	*i += ft_strmatch(line + *i, "0123456789");
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

void get_ambiance(char *line)
{
	t_ambiance *amb;
	int i;

	// ft_printf("line: '%s'\n", line);
	amb = malloc(sizeof(t_ambiance));
	i = ft_strmatch(line, " ");
	ft_printf("line: '%s', %d\n", line + i, i);

	amb->ratio = get_float(line, &i);
	ft_printf("ratio: %f\n", amb->ratio);
	i += ft_strmatch(line + i, " ");
	amb->color.r = get_int(line, &i);
	if (line[i] == ',')
		i++;
	else
		error_exit_msg(C_PARSE, E_PARSE);
	ft_printf("ratio: %f\nred %d\n", amb->ratio, amb->color.r);
}

void parse_line(char *line)
{
	// ft_printf("IN PARSE LINE: %s\n", line);
	if (line[0] == 'R')
		get_resolution(line + 1);
	if (line[0] == 'A')
		get_ambiance(line + 1);
}

void get_input(char *path)
{
	int fd;
	int ret;
	char *line;

	ret = 1;
	fd = open(path, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		parse_line(line);
		free(line);
	}
	close(fd);
}