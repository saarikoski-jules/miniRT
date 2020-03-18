/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:45:21 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 14:47:05 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_color	t_color;

int		get_int(char *line, int *i);
double	get_float(char *line, int *i);
void	skip_comma(char *line, int *i);
void	set_color(char *line, int *i, t_color *rgb);

#endif
