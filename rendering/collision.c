#include <stdio.h>//
#include "vec.h"
#include "rt.h"
#include "render.h"
#include <math.h>
#include <stdlib.h>

//TODO: Use defines for out of bounds, behind camera and inside obj

double sp_intersect(t_vec *ray_start, t_vec *ray, t_sp *sp)
{	
	t_vec *len;
	double b;
	double c;

	len = substract_vectors(ray_start, sp->pos);
	if (det_len_vec(len) <= sp->r)
		return (INSIDE_OBJ); //You're inside the circle
	b = 2.0 * get_dot_product(ray, len);
	c = get_dot_product(len, len) - pow(sp->r, 2);
	free(len);
	return (solve_quadratic(1.0, b, c));
}

double pl_intersect(t_vec *orien, t_vec *ray_start, t_vec *pos, t_vec *ray)
{
	t_vec *v_pl;
	double ln;
	double pln;
	double t;

	ln = get_dot_product(ray, orien);
	if (ln == 0)
		return (NO_INTERSECT);
	v_pl = substract_vectors(pos, ray_start);
	pln = get_dot_product(v_pl, orien);
	free(v_pl);
	t = pln / ln;
	if (t <= 0)
		return (NO_INTERSECT);
	return (t);
}

double sq_intersect(t_vec *ray_start, t_vec *ray, t_sq *sq)
{
	double	t;
	t_vec	*point;

	t = pl_intersect(sq->orien, ray_start, sq->point1, ray);
	if (t == INFINITY)
		return (INFINITY);
	point = find_point(ray_start, ray, t);
	if (point_within_line(sq->point1, sq->point2, point, sq->orien) > 0
	&&	point_within_line(sq->point2, sq->point3, point, sq->orien) > 0
	&&	point_within_line(sq->point3, sq->point4, point, sq->orien) > 0
	&&	point_within_line(sq->point4, sq->point1, point, sq->orien) > 0)
	{
		free(point);
		return (t);
	}
	free(point);
	return (-1);
}

double tr_intersect(t_vec *ray_start, t_vec *ray, t_tr *tr)
{
	double t;
	t_vec *point;
	t = pl_intersect(tr->orien, ray_start, tr->point1, ray);
	if (t == NO_INTERSECT)
		return (NO_INTERSECT);
	point = find_point(ray_start, ray, t);
	if (point_within_line(tr->point1, tr->point2, point, tr->orien) > 0
	&&	point_within_line(tr->point2, tr->point3, point, tr->orien) > 0
	&&	point_within_line(tr->point3, tr->point1, point, tr->orien) > 0)
	{
		free(point);
		return (t);
	}
	free(point);
	return (NO_INTERSECT);
}
