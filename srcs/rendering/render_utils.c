#include "color.h"
#include "libft.h"//
#include "error.h"
#include <stdlib.h>//
#include "render.h"
#include <math.h>
#include <stdio.h>

t_vec	*find_point(t_vec *start, t_vec *dir, double t)
{
	t_vec *dist;
	t_vec *point;

	dist = gen_coord(dir->x * t, dir->y * t, dir->z * t);
	point = add_vectors(start, dist);
	free(dist);
	return (point);
}

double	get_distance(t_vec *point1, t_vec *point2)
{
	double x;
	double y;
	double z;
	double d;
	
	x = pow(point1->x - point2->x, 2);
	y = pow(point1->y - point2->y, 2);
	z = pow(point1->z - point2->z, 2);
	d = sqrt(x + y + z);
	return (d);
}

double	point_within_line(t_vec *point1, t_vec *point2, t_vec *p, t_vec *orien)
{
	t_vec *edge;
	t_vec *to_p;
	t_vec *cross;
	double dot;

	edge = substract_vectors(point2, point1);
	to_p = substract_vectors(p, point1);
	cross = get_cross_product(edge, to_p);
	dot = get_dot_product(orien, cross);
	free(edge);
	free(to_p);
	free(cross);
	return (dot);
}
