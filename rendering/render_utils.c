#include "color.h"
#include "libft.h"//
#include "error.h"
#include <stdlib.h>//
#include "render.h"
#include <math.h>
#include <stdio.h>

unsigned int translate_color(t_color *color) // COLOR MIGHT NOT ALWAYS EXIST, PLEASE FIX WITH TEST.RT
{
	int rgb;
	// ft_printf("not broken?? %p\n", color);
	// ft_printf("%d,", color->g);
	// ft_printf("not broken?? %d, %d, %d\n", color->r, color->g, color->b);
	rgb = (color->r * pow(16, 4)) + (color->g * pow(16, 2)) + (color->b);
	return (rgb);
}

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
	// ft_printf("cross: (%f, %f, %f)\n", cross->x, cross->y, cross->z);
	dot = get_dot_product(orien, cross);
	// if (dot < 0)
	// {
		// t_vec *orien_2 = gen_coord(-orien->x, -orien->y, -orien->z);
		// dot = get_dot_product(orien_2, cross);
	// }
	free(edge);
	free(to_p);
	free(cross);
	// ft_printf("point_within_line: %f\n", dot);
	return (dot);
}

double	solve_quadratic(double a, double b, double c)
{
	double disc;
	double t;
	double t1;
	double t2;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (NO_INTERSECT);
	if (disc > 0)
	{
		t1 = ((-b - sqrt(disc)) / (2 * a));
		t2 = ((-b + sqrt(disc)) / (2 * a));
		if (t1 < t2)
			t = t1;
		else
			t = t2;
	}
	else if (disc == 0)
		t = -b / (2 * a);
	if (t < 0)
		return (NO_INTERSECT);
	return (t);
}