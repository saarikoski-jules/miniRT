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

	i = 1;
	res = malloc(sizeof(t_resolution));
	if (!res)
		exit(0);
	while (line[i] == ' ')
		i++;
	res->res_x = ft_atoi(line + i);
	while (ft_strchr("0123456789", line[i]) && line[i] != '\0')
		i++;
	res->res_y = ft_atoi(line + i);
	ft_printf("x = %d, y = %d\n", res->res_x, res->res_y);
	//if can't store, exit and print an error
	//make function that will exit and print desired error message?
}

double get_float_part(char *line)
{
	ft_printf("get_float_part: %s\n", line);
	int i;

	i = 1;
	int num = ft_atoi(line + i);
	int len = ft_numlen(num);
	len *= -1;

	double flt_part = 2 * pow(10, len);
	ft_printf("%d, %d, %f\n", num, len, flt_part);
	return (flt_part);
}
//TODO smol fsm's
//TODO ft_pow and ft_atof

void get_ambiance(char *line)
{
	t_ambiance *amb;
	int i;

	i = 1;
	amb = malloc(sizeof(t_ambiance));
	if (!amb)
		exit(0);
	while (line[i] == ' ')
		i++;
	// ft_printf("%s\n", line + i);
	// ft_printf("%d\n", ft_atoi(line + i));
	double rat = ft_atoi(line + i);
	i++;
	ft_printf("%f\n", rat);
	rat += get_float_part(line + i);
	ft_printf("rat: %f\n", rat);
	amb->ratio = rat;
}

void parse_line(char *line)
{
	// ft_printf("IN PARSE LINE: %s\n", line);
	if (line[0] == 'R')
		get_resolution(line);
	if (line[0] == 'A')
		get_ambiance(line);
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