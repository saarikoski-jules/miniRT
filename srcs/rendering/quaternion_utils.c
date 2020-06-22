/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 13:07:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 15:03:26 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vec.h"
#include "error.h"
#include <math.h>

t_qua	*gen_q_conjugate(t_qua *q)
{
	t_qua *q_c;

	q_c = (t_qua*)e_malloc(sizeof(t_qua));
	q_c->w = q->w;
	q_c->vector = gen_coord(-q->vector->x,
							-q->vector->y,
							-q->vector->z);
	return (q_c);
}

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

void	free_quaternion(t_qua **q)
{
	free((*q)->vector);
	free(*q);
	(*q) = NULL;
}

t_qua	*build_unit_q(double w, double x, double y, double z)
{
	t_qua *q;
	t_qua *q_u;

	q = (t_qua *)e_malloc(sizeof(t_qua));
	q->w = w;
	q->vector = gen_coord(x, y, z);
	q_u = gen_unit_quaternion(q);
	free_quaternion(&q);
	// free(q->vector);
	// free(q);
	return (q_u);
}

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
