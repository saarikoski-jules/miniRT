/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 17:13:02 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/15 17:17:23 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "error.h"
#include <math.h>
#include "libft.h"//

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

t_qua *calculate_q_values(t_vec *base_u, t_vec *orien_u, t_vec *axis_u)
{
	double dot;
	double angle;
	double half_sin;
	double half_cos;
	t_qua *q;
	t_qua *q_u;

	q = (t_qua *)e_malloc(sizeof(t_qua));
	dot = get_dot_product(base_u, orien_u);
	angle = acos(dot);
	half_sin = sin(0.5 * angle);
	half_cos = cos(0.5 * angle);
	q->w = half_cos;
	q->vector = gen_coord(half_sin * axis_u->x, half_sin * axis_u->y, half_sin * axis_u->z);
	q_u = gen_unit_quaternion(q);
	free(q);
	return(q_u);
}

t_qua *parallel_vecs(t_vec *base_u, t_vec *orien_u)
{
	t_qua *q;

	q = (t_qua *)e_malloc(sizeof(t_qua));
	if (base_u->x == orien_u->x && base_u->y == orien_u->y && base_u->z == orien_u->z)
		q->w = 1.0;
	else
		q->w = 0.0;
	q->vector = gen_coord(0.0, 0.0, 0.0);
	return (q);
}

t_qua *determine_quaternion(t_vec *orien, t_vec *base)
{
	t_vec *orien_u;
	t_vec *base_u;
	t_vec *axis;
	t_vec *axis_u;
	t_qua *q;

	if (det_len_vec(orien) == 0.0 || det_len_vec(base) == 0.0)
		 error_exit_msg(C_R_INVALID_ARG_Q, E_R_INVALID_ARG_Q);
	orien_u = set_vec_len(orien, 1.0);
	base_u = set_vec_len(base, 1.0);
	axis = get_cross_product(base_u, orien_u);
	if (axis->x == 0.0 && axis->y == 0.0 && axis->z == 0.0)
		q = parallel_vecs(base_u, orien_u);
	else
	{
		axis_u = set_vec_len(axis, 1.0);
		q = calculate_q_values(base_u, orien_u, axis_u);
		free(axis_u);
	}
	free(orien_u);
	free(base_u);
	free(axis);
	return (q);
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


