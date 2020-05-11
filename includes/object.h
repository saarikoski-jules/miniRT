/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 13:07:10 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/11 14:40:34 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECT_H
# define OBJECT_H

# include "vec.h"
# include "quaternion.h"//
# include "color.h"
/*
** OBJECT STRUCTS
*/

typedef struct	s_sp
{
	t_vec			*pos;
	double			dia;
	double			r;
}				t_sp;

typedef struct	s_pl
{
	t_vec			*pos;
	t_vec			*orien;
}				t_pl;

typedef struct	s_sq
{
	t_vec			*pos;
	t_vec			*orien;
	double			side;
	t_vec			*point1;
	t_vec			*point2;
	t_vec			*point3;
	t_vec			*point4;
}				t_sq;

typedef struct	s_cy
{
	t_vec			*pos;
	t_vec			*orien;
	double			dia;
	double			h;
	t_vec			*end1;
	t_vec			*end2;
	double			r;
	t_qua			*q;
}				t_cy;

typedef struct	s_tr
{
	t_vec	*point1;	
	t_vec	*point2;	
	t_vec	*point3;
	t_vec	*orien;	
}				t_tr;

/*
** ORGANIZE
*/

typedef union	u_type
{
	t_sp	*sp;
	t_pl	*pl;
	t_sq	*sq;
	t_cy	*cy;
	t_tr	*tr;
}				t_type;

typedef enum	e_identifier
{
	sp,
	pl,
	sq,
	cy,
	tr,
}				t_identifier;

/*
** MAIN OBJECT LIST
*/

typedef struct	s_obj
{
	t_identifier	id;
	t_color			*color;
	t_type			type;
	struct s_obj	*next;
}				t_obj;

#endif
