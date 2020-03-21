/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 13:35:20 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/18 14:45:56 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** GENERAL
*/


# include "vec.h"//
# include "color.h"//
# include "object.h"//
// # include "parse.h"//

/*
** DATA STRUCTS
*/

typedef struct	s_resolution
{
	unsigned int res_x;
	unsigned int res_y;
}				t_resolution;


typedef struct	s_ambiance
{
	double		ratio;
	t_color		*color;
}				t_ambiance;

typedef struct	s_camera
{
	t_vec			*pos;
	t_vec			*orien;
	int				fov;
	struct s_camera *next;
}				t_camera;

typedef struct	s_light
{
	t_vec			*pos;
	double			brightness;
	t_color			*color;
	struct s_light *next;
}				t_light;

typedef struct	s_rt_scene
{
	t_resolution	*res;
	t_ambiance		*amb;
	t_camera		*cam;
	t_light			*light;
	t_obj			*obj;
}				t_rt_scene;

t_rt_scene	*get_scene(char *path);
void		trace_them_rays(t_rt_scene *scene);
// void		get_input(char *path, t_rt_scene **scene);
// void		parse_line(char *line, t_rt_scene **scene);

#endif
