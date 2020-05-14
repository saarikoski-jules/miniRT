/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 17:13:02 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/14 18:52:48 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "error.h"
#include <math.h>

t_qua	*gen_unit_quaternion(t_qua *q)
{
	t_qua	*q_u;
	double	val;
	double	len;

	q_u = (t_qua*)e_malloc(sizeof(t_qua));
	val = pow(q->w, 2) +
				pow(q->vector->x, 2) +
				pow(q->vector->y, 2) +
				pow(q->vector->z, 2);
	len = sqrt(val);
	q_u->w = q->w / len;
	q_u->vector = gen_coord(q->vector->x / len,
							q->vector->y / len,
							q->vector->z / len);
	return (q_u);
}

t_qua *determine_quaternion(t_vec *orien, t_vec *base)
{
	if (det_len_vec(orien) == 0 || det_len_vec(base) == 0)
		 error_exit_msg(C_R_INVALID_ARG_Q, E_R_INVALID_ARG_Q);
	t_qua *q;
	t_vec *orien_u;
	orien_u = set_vec_len(orien, 1.0);

	q = (t_qua *)e_malloc(sizeof(t_qua));
	t_vec *base_u = set_vec_len(base, 1);
	double dot = get_dot_product(base_u, orien_u);
	double angle = acos(dot);
	t_vec *axis = get_cross_product(base_u, orien_u);
	if (axis->x == 0 && axis->y == 0 && axis->z == 0)
	{
		if (base_u->x == orien_u->x && base_u->y == orien_u->y && base_u->z == orien_u->z)
		{
			q->w = 1.0;
		}
		else
		{
			q->w = 0.0;
		}
		q->vector = gen_coord(0.0, 0.0, 0.0);
		return (q);
	}
	t_vec *axis_u = set_vec_len(axis, 1.0);
	double half_sin = sin(0.5 * angle);
	double half_cos = cos(0.5 * angle);
	q->w = half_cos;
	q->vector = gen_coord(half_sin * axis_u->x, half_sin * axis_u->y, half_sin * axis_u->z);
	t_qua *q_u = gen_unit_quaternion(q);
	return (q_u);
}

t_qua *gen_q_conjugate(t_qua *q)
{
	t_qua *q_c;

	q_c = (t_qua*)e_malloc(sizeof(t_qua));
	q_c->w = q->w;
	q_c->vector = gen_coord(-q->vector->x,
							-q->vector->y,
							-q->vector->z);
	return (q_c);
}

t_vec *orient_vector(t_qua *q, t_vec *v)
{
	t_qua *q_con;

	if (q->w == 0.0 && q->vector->x == 0.0 && q->vector->y == 0.0 && q->vector->z == 0.0)
		return (gen_coord(-v->x, v->y * -1, v->z * -1));
	q_con = gen_q_conjugate(q);
	double tmp = 2 * get_dot_product(q->vector, v);
	t_vec *first = gen_coord(q->vector->x * tmp, q->vector->y * tmp, q->vector->z * tmp);
	double s2 = pow(q->w, 2);
	double dotu = get_dot_product(q_con->vector, q->vector);
	double totimes = s2 + dotu;
	t_vec *second = gen_coord(totimes * v->x, totimes * v->y, totimes * v->z);
	double stwo = q->w * 2;
	t_vec *cross = get_cross_product(q->vector, v); //fix if vectors point in opposite directions
	t_vec *crosstimes = gen_coord(cross->x * stwo, cross->y * stwo, cross->z * stwo);
	t_vec *semifinal = add_vectors(first, second);
	t_vec *final = add_vectors(semifinal, crosstimes);
	return (final);
}
