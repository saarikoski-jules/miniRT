/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiply_quaternions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 12:19:09 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:23:46 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "error.h"

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
	return (final);
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
