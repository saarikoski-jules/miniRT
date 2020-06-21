/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_vec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 17:17:13 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 15:03:28 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vec.h"
#include "error.h"
#include <math.h>

static t_vec	*parallel_vecs(t_qua *q, t_vec *v)
{
	if (q->w == 0.0)
		return (gen_coord(-v->x, -v->y, -v->z));
	return (gen_coord(v->x, v->y, v->z));	
}

static t_qua	*gen_pure_quat(t_vec *v)
{
	t_vec	*v_u;
	t_qua	*q;
	
	v_u = set_vec_len(v, 1.0);
	q = (t_qua *)e_malloc(sizeof(t_qua));
	q->w = 0.0;
	q->vector = gen_coord(v_u->x, v_u->y, v_u->z);
	free(v_u);
	return (q);
}

t_vec			*orient_vector(t_qua *q, t_vec *v)
{
	t_qua *q_v;
	t_qua *tmp;
	t_qua *q_c;
	t_qua *final;
	t_vec *vec_oriented;

	if (det_len_vec(q->vector) == 0)
		return (parallel_vecs(q, v));
	q_v = gen_pure_quat(v);
	tmp = multiply_quats(q, q_v);
	q_c = gen_q_conjugate(q);
	final = multiply_quats(tmp, q_c);
	vec_oriented = gen_coord(final->vector->x,
								final->vector->y,
								final->vector->z);
	free_quaternion(&q_v);
	free_quaternion(&tmp);
	free_quaternion(&q_c);
	free_quaternion(&final);
	return (vec_oriented);
}
