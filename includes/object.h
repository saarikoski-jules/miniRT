/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 14:53:21 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/17 14:52:12 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "rt.h"

/*
** OBJECT STRUCTS
*/

typedef struct	s_sp
{
	t_vec			pos;
	unsigned int	dia;
}				t_sp;

typedef struct	s_pl
{
	t_vec			pos;
	t_vec			orien;
}				t_pl;

typedef struct	s_sq
{
	t_vec			pos;
	t_vec			orien;
	unsigned int	side;
}				t_sq;

typedef struct	s_cy
{
	t_vec			pos;
	t_vec			orien;
	unsigned int	dia;
	unsigned int	h;
}				t_cy;

typedef struct	s_tr
{
	t_vec	point1;	
	t_vec	point2;	
	t_vec	point3;	
}				t_tr;

/*
** ORGANIZE
*/

typedef union	u_type
{
	t_sp	sp;
	t_pl	pl;
	t_sq	sq;
	t_cy	cy;
	t_tr	tr;
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
	t_identifier	type;
	t_color			color;
	t_type			object;
	s_obj			*next;
}				t_obj;

#endif
