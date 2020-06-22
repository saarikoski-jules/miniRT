/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sq.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 18:04:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 18:09:32 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "error.h"
#include "parse.h"

static t_vec	*position_corner(t_vec *corner, t_qua *q, t_vec *pos)
{
	t_vec *p;
	t_vec *oriented;

	p = orient_vector(q, corner);
	oriented = add_vectors(pos, p);
	free(p);
	return (oriented);
}

static void		find_square_corners(t_sq **square, t_qua *q)
{
	t_vec *c1;
	t_vec *c2;
	t_vec *c3;
	t_vec *c4;

	c1 = gen_coord(-(*square)->side / 2, (*square)->side / 2, 0);
	c2 = gen_coord(-(*square)->side / 2, -(*square)->side / 2, 0);
	c3 = gen_coord((*square)->side / 2, -(*square)->side / 2, 0);
	c4 = gen_coord((*square)->side / 2, (*square)->side / 2, 0);
	(*square)->point1 = position_corner(c1, q, (*square)->pos);
	(*square)->point2 = position_corner(c2, q, (*square)->pos);
	(*square)->point3 = position_corner(c3, q, (*square)->pos);
	(*square)->point4 = position_corner(c4, q, (*square)->pos);
	free(c1);
	free(c2);
	free(c3);
	free(c4);
}

t_sq			*get_square(char *line, size_t *i)
{
	t_sq	*square;
	t_qua	*q;
	t_vec	*base;

	square = (t_sq*)e_malloc(sizeof(t_sq));
	square->pos = get_vec(line, i);
	square->orien = get_vec(line, i);
	validate_orien(&square->orien);
	if (square->orien->x == 0 &&
		square->orien->y == 0 &&
		square->orien->z == -1)
		square->orien->z = 1;
	square->side = get_float(line, i);
	base = gen_coord(0, 0, 1);
	q = determine_quaternion(square->orien, base);
	find_square_corners(&square, q);
	if (square->side < 0.0)
		error_exit_msg(C_INVALID_SQ, E_INVALID_SQ);
	free(base);
	free_quaternion(&q);
	return (square);
}
