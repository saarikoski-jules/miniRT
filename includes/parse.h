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
# include <stdlib.h>//
# include "rt.h"//
# include "object.h"//

typedef struct s_color	t_color;

int		get_int(char *line, size_t *i);
double	get_float(char *line, size_t *i);
t_vec	*get_vec(char *line, size_t *i);
t_color	*get_color(char *line, size_t *i);
void	skip_comma(char *line, size_t *i);

// void	get_camera(char *line);
t_resolution	*get_resolution(char *line);
t_ambiance		*get_ambiance(char *line);
t_light			*add_light(char *line, t_light *first_light);
t_camera		*add_camera(char *line, t_camera *first_camera);
t_obj			*add_object(char *line, t_obj *first_obj);
// void	get_light(char *line);
// void	get_object(char *line);
t_sp	*get_sphere(char *line, size_t *i);
t_pl	*get_plane(char *line, size_t *i);
t_sq	*get_square(char *line, size_t *i);
t_cy	*get_cylinder(char *line, size_t *i);
t_tr	*get_triangle(char *line, size_t *i);

void	validate_fov(int fov);
void	validate_orien(t_vec *orien);
// void	validate_color(t_color *color);

void	validate_int(char *line);
void	validate_float(char *line);
void	validate_file(char *path);

#endif
