#include <stdio.h>//
#include "object.h"
#include "parse.h"
#include "libft.h"
#include "error.h"
#include "quaternion.h"//
#include "vec.h"//


t_sp	*get_sphere(char *line, size_t *i)
{
	t_sp	*sphere;

	sphere = (t_sp*)malloc(sizeof(t_sp));
	if (!sphere)
		error_exit_errno();
	sphere->pos = get_vec(line, i);
	*i += ft_strmatch(line + *i, " ");
	sphere->dia = get_float(line, i);
	if (sphere->dia < 0.0)
		error_exit_msg(C_INVALID_SP, E_INVALID_SP);
	sphere->r = sphere->dia * 0.5;
	return (sphere);
}

t_pl	*get_plane(char *line, size_t *i)
{
	t_pl *plane;

	plane = (t_pl*)malloc(sizeof(t_pl));
	if (!plane)
		error_exit_errno();
	plane->pos = get_vec(line, i);
	plane->orien = get_vec(line, i);
	validate_orien(&plane->orien);
	return (plane);
}

t_vec *position_corner(t_vec *corner, t_qua *q, t_vec *pos)
{
	t_vec *p;
	t_vec *oriented;

	p = orient_vector(q, corner);
	oriented = add_vectors(pos, p);
	free(p);
	return (oriented);
}

void find_square_corners(t_sq **square, t_qua *q)
{
	t_vec *c1;
	t_vec *c2;
	t_vec *c3;
	t_vec *c4;

	c1 = gen_coord(-(*square)->side/2, (*square)->side/2, 0);
	c2 = gen_coord(-(*square)->side/2, -(*square)->side/2, 0);
	c3 = gen_coord((*square)->side/2, -(*square)->side/2, 0);
	c4 = gen_coord((*square)->side/2, (*square)->side/2, 0);
	(*square)->point1 = position_corner(c1, q, (*square)->pos);
	(*square)->point2 = position_corner(c2, q, (*square)->pos);
	(*square)->point3 = position_corner(c3, q, (*square)->pos);
	(*square)->point4 = position_corner(c4, q, (*square)->pos);
	free(c1);
	free(c2);
	free(c3);
	free(c4);
}

t_sq	*get_square(char *line, size_t *i)
{
	t_sq	*square;
	t_qua	*q;
	t_vec	*base;

	square = (t_sq*)malloc(sizeof(t_sq));
	if (!square)
		error_exit_errno();
	square->pos = get_vec(line, i);
	square->orien = get_vec(line, i);
	validate_orien(&square->orien);
	if (square->orien->x == 0 && square->orien->y == 0 && square->orien->z == -1)
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

void	det_cy_data(t_cy **cy)
{
	t_vec *mov;
	t_vec *base;

	base = gen_coord(0, 0, -1);
	(*cy)->r = (*cy)->dia * 0.5;
	mov = set_vec_len((*cy)->orien, (*cy)->h * 0.5);
	(*cy)->end2 = add_vectors((*cy)->pos, mov);
	(*cy)->end1 = substract_vectors((*cy)->pos, mov);
	free(mov);
	(*cy)->q = determine_quaternion(base, (*cy)->orien);
	free(base);
}

t_cy	*get_cylinder(char *line, size_t *i)
{
	t_cy	*cylinder;

	cylinder = (t_cy *)e_malloc(sizeof(t_cy));
	cylinder->pos = get_vec(line, i);
	cylinder->orien = get_vec(line, i);
	validate_orien(&cylinder->orien);
	cylinder->dia = get_float(line, i);
	cylinder->h = get_float(line, i);
	if (cylinder->dia < 0.0 || cylinder->h < 0.0)
		error_exit_msg(C_INVALID_CY, E_INVALID_CY);
	det_cy_data(&cylinder);
	return (cylinder);
}

t_tr	*get_triangle(char *line, size_t *i)
{
	t_tr	*triangle;
	t_vec	*BA;
	t_vec	*CA;
	t_vec	*normal;

	triangle = (t_tr *)e_malloc(sizeof(t_tr));
	triangle->point1 = get_vec(line, i);
	triangle->point2 = get_vec(line, i);
	triangle->point3 = get_vec(line, i);
	BA = substract_vectors(triangle->point2, triangle->point1);
	CA = substract_vectors(triangle->point3, triangle->point1);
	normal = get_cross_product(BA, CA);
	triangle->orien = set_vec_len(normal, 1.0);
	free(BA);
	free(CA);
	free(normal);
	return (triangle);
}
