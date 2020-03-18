/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:45:21 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 15:46:53 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_color	t_color;

int		get_int(char *line, size_t *i);
double	get_float(char *line, size_t *i);
t_vec	*get_vec(char *line, size_t *i);
void	get_camera(char *line);
void	skip_comma(char *line, size_t *i);
t_color	*get_color(char *line, size_t *i);

void	validate_fov(int fov);
void	validate_orien(t_vec *orien);
void	validate_color(t_color *color);

void	validate_int(char *line);
void	validate_float(char *line);

#endif
