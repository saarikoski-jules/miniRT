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

void parse_line(char *line)
{
	// ft_printf("IN PARSE LINE: %s\n", line);
	if (line[0] == 'R')
		get_resolution(line + 1);
	else if (line[0] == 'A')
		get_ambiance(line + 1);
	else if (ft_strncmp(line, "l ", 2) == 0)
		get_light(line + 1);
	else if (ft_strncmp(line, "c ", 2) == 0)
		get_camera(line + 1);
	else if (ft_strncmp(line, "sp", 2) == 0
		||	ft_strncmp(line, "pl", 2) == 0
		||	ft_strncmp(line, "sq", 2) == 0
		||	ft_strncmp(line, "cy", 2) == 0
		||	ft_strncmp(line, "tr", 2) == 0)
	{
		get_object(line);
	}
	else
		error_exit_msg(C_PARSE, E_PARSE);
}

void get_input(char *path)
{
	int fd;
	int ret;
	char *line;

	validate_file(path);
	ret = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_strncmp(line, "\0", 1) != 0)
			parse_line(line);
		free(line);
	}
	close(fd);
}