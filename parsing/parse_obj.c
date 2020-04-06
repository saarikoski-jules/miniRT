
#include "object.h"
#include "parse.h"
#include "libft.h"
#include "error.h"
#include "quaternion.h"//


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
	validate_orien(plane->orien);
	return (plane);
}

void find_square_corners(t_sq **square)
{
	t_vec *c1;
	t_vec *c2;
	t_vec *c3;
	t_vec *c4;

	c1 = gen_coord(-(*square)->side/2, (*square)->side/2, 0);
	c2 = gen_coord(-(*square)->side/2, -(*square)->side/2, 0);
	c3 = gen_coord((*square)->side/2, -(*square)->side/2, 0);
	c4 = gen_coord((*square)->side/2, (*square)->side/2, 0);

	// ft_printf("c1: (%f, %f, %f)\nc2: (%f, %f, %f)\nc3: (%f, %f, %f)\nc4: (%f, %f, %f)\n", c1->x, c1->y, c1->z, c2->x, c2->y, c2->z, c3->x, c3->y, c3->z, c4->x, c4->y, c4->z);

	t_vec *base = gen_coord(0, 0, 1);

	t_qua *q = determine_quaternion((*square)->orien, base);

	t_vec *p1 = orient_vector(q, c1);
	t_vec *p2 = orient_vector(q, c2);
	t_vec *p3 = orient_vector(q, c3);
	t_vec *p4 = orient_vector(q, c4); //lets hope this is 

	(*square)->point1 = add_vectors((*square)->pos, p1);
	(*square)->point2 = add_vectors((*square)->pos, p2);
	(*square)->point3 = add_vectors((*square)->pos, p3);
	(*square)->point4 = add_vectors((*square)->pos, p4); //lets hope this is correct



	ft_printf("c1: (%f, %f, %f)\nc2: (%f, %f, %f)\nc3: (%f, %f, %f)\nc4: (%f, %f, %f)\n", (*square)->point1->x, (*square)->point1->y, (*square)->point1->z, (*square)->point2->x, (*square)->point2->y, (*square)->point2->z, (*square)->point3->x, (*square)->point3->y, (*square)->point3->z, (*square)->point4->x, (*square)->point4->y, (*square)->point4->z);

	// (*square)->point1 = orient_vector()

	//find corners on a plane with orientation
	//move points using quaternion
}

t_sq	*get_square(char *line, size_t *i)
{
	t_sq	*square;

	square = (t_sq*)malloc(sizeof(t_sq));
	if (!square)
		error_exit_errno();
	square->pos = get_vec(line, i);
	square->orien = get_vec(line, i);
	validate_orien(square->orien);
	square->side = get_float(line, i);
	find_square_corners(&square);
	if (square->side < 0.0)
		error_exit_msg(C_INVALID_SQ, E_INVALID_SQ);
	return (square);
}

t_cy	*get_cylinder(char *line, size_t *i)
{
	t_cy	*cylinder;

	cylinder = (t_cy*)malloc(sizeof(t_cy));
	if (!cylinder)
		error_exit_errno();
	cylinder->pos = get_vec(line, i);
	cylinder->orien = get_vec(line, i);
	validate_orien(cylinder->orien);
	cylinder->dia = get_float(line, i);
	cylinder->h = get_float(line, i);
	if (cylinder->dia < 0.0 || cylinder->h < 0.0)
		error_exit_msg(C_INVALID_CY, E_INVALID_CY);
	return (cylinder);
}

t_tr	*get_triangle(char *line, size_t *i)
{
	t_tr	*triangle;

	triangle = (t_tr*)malloc(sizeof(t_tr));
	if (!triangle)
		error_exit_errno();
	triangle->point1 = get_vec(line, i);
	triangle->point2 = get_vec(line, i);
	triangle->point3 = get_vec(line, i);
	return (triangle);
}
