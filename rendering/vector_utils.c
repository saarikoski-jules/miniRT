/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 17:08:07 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/14 17:08:08 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>
#include "error.h"

t_vec	*gen_coord(double x, double y, double z)
{
	t_vec *vector;

	vector = (t_vec*)e_malloc(sizeof(t_vec));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
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

double	det_len_vec(t_vec *vector)
{
	double len;
	double x;
	double y;
	double z;

	x = pow(vector->x, 2);
	y = pow(vector->y, 2);
	z = pow(vector->z, 2);
	len = sqrt(x + y + z);
	return (len);
}

t_vec	*set_vec_len(t_vec *vector, double len)
{
	double vec_len;
	t_vec *new_vec;

	new_vec = (t_vec*)e_malloc(sizeof(t_vec));
	vec_len = det_len_vec(vector);
	new_vec->x = (vector->x / vec_len) * len;
	new_vec->y = (vector->y / vec_len) * len;
	new_vec->z = (vector->z / vec_len) * len;
	return (new_vec);
}
