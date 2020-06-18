/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_vec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 17:17:13 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/18 16:29:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vec.h"
#include "error.h"
#include <math.h>

/*
** q1*q2	= [w1, v1][w2, v1]
**			= [w1 * w2 - v1 * v2,
**				w1 * v2 + w2 * v1 + v1 x v2]		
*/

static t_vec	*multiply_q_vec(t_qua *q1, t_qua *q2)
{
	t_vec *q2_mul;
	t_vec *q1_mul;
	t_vec *cross;
	t_vec *mul;
	t_vec *final;
	
	q2_mul = gen_coord(q2->vector->x * q1->w,
					q1->w * q2->vector->y,
					q1->w * q2->vector->z);
	q1_mul = gen_coord(q1->vector->x * q2->w,
					q2->w * q1->vector->y,
					q2->w * q1->vector->z);
	cross = get_cross_product(q1->vector, q2->vector);
	mul = add_vectors(q2_mul, q1_mul);
	final = add_vectors(mul, cross);
	free(q2_mul);
	free(q1_mul);
	free(cross);
	free(mul);
	return(final);	
}

t_qua			*multiply_quats(t_qua *q1, t_qua *q2)
{
	double	w;
	t_qua	*final_q;

	final_q = (t_qua *)e_malloc(sizeof(t_qua));
	w = (q1->w * q2->w) - get_dot_product(q1->vector, q2->vector);
	final_q->w = w;
	final_q->vector = multiply_q_vec(q1, q2);
	return (final_q);
}

t_vec			*orient_vector(t_qua *q, t_vec *v)
{
	t_vec *v_u;
	t_qua *q_v;
	t_qua *tmp;
	t_qua *q_c;
	t_qua *final;

	v_u = set_vec_len(v, 1.0);
	q_v = (t_qua *)e_malloc(sizeof(t_qua));
	q_v->w = 0.0;
	q_v->vector = gen_coord(v_u->x, v_u->y, v_u->z);
	tmp = multiply_quats(q, q_v);
	q_c = gen_q_conjugate(q);
	final = multiply_quats(tmp, q_c);
	return (final->vector);
}
