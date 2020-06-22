/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 12:01:57 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:04:45 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "error.h"
#include <math.h>

double	solve_quadratic(double a, double b, double c)
{
	double disc;
	double t;
	double t1;
	double t2;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (NO_INTERSECT);
	else if (disc > 0)
	{
		t1 = ((-b - sqrt(disc)) / (2 * a));
		t2 = ((-b + sqrt(disc)) / (2 * a));
		if (t1 < t2)
			t = t1;
		else
			t = t2;
	}
	else
		t = -b / (2 * a);
	return (t);
}

t_vec	*add_vectors(t_vec *vec1, t_vec *vec2)
{
	t_vec *vector;

	vector = gen_coord(vec1->x + vec2->x,
						vec1->y + vec2->y,
						vec1->z + vec2->z);
	return (vector);
}

t_vec	*substract_vectors(t_vec *vec1, t_vec *vec2)
{
	t_vec *vector;

	vector = gen_coord(vec1->x - vec2->x,
					vec1->y - vec2->y,
					vec1->z - vec2->z);
	return (vector);
}

t_vec	*get_cross_product(t_vec *vec1, t_vec *vec2)
{
	t_vec *cross;

	cross = (t_vec*)e_malloc(sizeof(t_vec));
	cross->x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
	cross->y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
	cross->z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
	return (cross);
}

double	get_dot_product(t_vec *vec1, t_vec *vec2)
{
	double x;
	double y;
	double z;
	double sum;

	x = vec1->x * vec2->x;
	y = vec1->y * vec2->y;
	z = vec1->z * vec2->z;
	sum = x + y + z;
	return (sum);
}
