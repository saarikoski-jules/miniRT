/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 17:08:07 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:09:37 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "render.h"
#include <math.h>

t_vec	*gen_coord(double x, double y, double z)
{
	t_vec *vector;

	vector = (t_vec*)e_malloc(sizeof(t_vec));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
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

t_vec		*apply_epsilon(t_vec *point, t_vec *ray)
{
	t_vec *new;
	t_vec *eps;

	eps = set_vec_len(ray, EPSILON);
	new = add_vectors(point, eps);
	free(eps);
	return (new);
}

t_vec		*find_len_and_get_u(double *len, t_vec *from, t_vec *to)
{
	t_vec *vec;
	t_vec *vec_u;

	vec = substract_vectors(from, to);
	*len = det_len_vec(vec);
	vec_u = set_vec_len(vec, 1);
	free(vec);
	return (vec_u);
}
