/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 13:35:20 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/15 14:09:02 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

typedef struct	s_resolution
{
	int res_x;
	int res_y;
}				t_resolution;

typedef struct	s_lighting
{
	double	ratio;
	int		red;
	int		green;
	int		blue;
}				t_lighting;

typedef struct	s_coord
{
	double x;
	double y;
	double z;
}				t_coord;


typedef struct	s_camera
{
	t_coord pos;
	t_coord dir;
	int		fov;
}				t_camera;

typedef	struct	s_rt_data
{
	t_resolution	R;
	t_lighting		L;
	
}				t_rt_data;


#endif