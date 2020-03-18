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
	{
		ft_printf("oops\n");
		exit(0);
	}
	res->res_x = ft_atoi(line + i);
	i += ft_strmatch(line + i, "0123456798");
	i += ft_strmatch(line + i, " ");
	if (ft_strchr("0123456789", line[i]) == NULL)
	{
		ft_printf("oops\n");
		exit(0);
	}
	res->res_y = ft_atoi(line + i);
	ft_printf("res_x %d, rez_y %d\n", res->res_x, res->res_y);
}

void parse_line(char *line)
{
	// ft_printf("IN PARSE LINE: %s\n", line);
	if (line[0] == 'R')
		get_resolution(line + 1);
	// if (line[0] == 'A')
		// get_ambiance(line);
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