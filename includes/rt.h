/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 13:35:20 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/15 15:43:31 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** GENERAL
*/

typedef struct	s_vec
{
	double x;
	double y;
	double z;
}				t_vec;

typedef struct	s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_color;

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
	t_color		color;
}				t_ambiance;

typedef struct	s_camera
{
	t_vec			pos;
	t_vec			orien;
	int				fov;
	struct s_camera *next;
}				t_camera;

typedef struct	s_light
{
	t_vec			pos;
	int				brightness;
	t_color			color;
	struct s_light *next;
}				t_light;

#endif
