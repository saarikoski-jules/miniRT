/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 16:02:26 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/18 15:04:54 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"
#include "error.h"
#include "parse.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

void get_resolution(char *line)
{
	t_resolution	*res;
	size_t			i;

	res = malloc(sizeof(t_resolution));
	i = ft_strmatch(line, " ");
	res->res_x = get_int(line, &i);
	i += ft_strmatch(line + i, " ");
	res->res_y = get_int(line, &i);
	ft_printf("res_x %d, res_y %d\n", res->res_x, res->res_y);
}

void get_ambiance(char *line)
{
	t_ambiance	*amb;
	size_t		i;

	amb = malloc(sizeof(t_ambiance));
	i = ft_strmatch(line, " ");
	amb->ratio = get_float(line, &i);
	i += ft_strmatch(line + i, " ");
	set_color(line, &i, &(amb->color));
	ft_printf("ratio: %f\nr: %d\ng: %d\nb: %d\n", amb->ratio, amb->color.r, amb->color.g, amb->color.b);
}

void parse_line(char *line)
{
	// ft_printf("IN PARSE LINE: %s\n", line);
	if (line[0] == 'R')
		get_resolution(line + 1);
	if (line[0] == 'A')
		get_ambiance(line + 1);
	else if (line[0] == 'c')
		get_camera(line + 1);
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