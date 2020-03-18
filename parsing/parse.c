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

	i = 0;
	res = (t_resolution*)malloc(sizeof(t_resolution));
	res->res_x = get_int(line, &i);
	res->res_y = get_int(line, &i);
	if (res->res_x < 0 || res->res_y < 0)
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	i += ft_strmatch(line + i, " ");
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	// ft_printf("Resolution:\nres_x %d, res_y %d\n\n", res->res_x, res->res_y);
}

void get_ambiance(char *line)
{
	t_ambiance	*amb;
	size_t		i;

	amb = (t_ambiance*)malloc(sizeof(t_ambiance));
	i = 0;
	amb->ratio = get_float(line, &i);
	if (amb->ratio > 1.0 || amb->ratio < 0.0)
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	amb->color = get_color(line, &i);
	i += ft_strmatch(line + i, " ");
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	// ft_printf("Ambiance:\nratio: %f\nr: %d\ng: %d\nb: %d\n\n", amb->ratio, amb->color->r, amb->color->g, amb->color->b);
}

void get_light(char *line)
{
	size_t		i;
	t_light	*light;

	light = ft_calloc(1, sizeof(t_camera));
	if (light == NULL)
		error_exit_errno();
	i = 0;
	light->pos = get_vec(line, &i);
	light->brightness = get_float(line, &i);
	if (light->brightness > 1 || light->brightness < 0)
		error_exit_msg(C_INVALID_LIGHT, E_INVALID_LIGHT);
	light->color = get_color(line, &i);
	i += ft_strmatch(line + i, " ");
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_LIGHT, E_INVALID_LIGHT);
	// ft_printf("Light:\ncoords, x: %f, y: %f, z: %f\nbrightness: %f\ncolor: r: %d, g: %d, b: %d\n\n", light->pos->x, light->pos->y,  light->pos->z, light->brightness, light->color->r, light->color->g, light->color->b);
}

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