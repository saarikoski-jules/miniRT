/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_vec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 17:17:13 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/15 17:34:16 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vec.h"
#include <math.h>
#include "libft.h"//


/*
v_new	= q*v*q_con
		= (w,qv)(0,v)(w,-qv) //scalar part results in 0
		= 2(qv⋅v)qv+(w2−qv⋅qv)v+2w(qv×v)
		= 2(dot(qv,v)*qv) + (w*2*dot(-qv,qv)*v) + (2*w*cross(qv,v))
*/

static t_vec *orient_vec_util_two(t_qua *q, t_vec *v)
{
	t_qua	*q_con;
	double	mul;
	t_vec	*vec;
	
	q_con = gen_q_conjugate(q);
	mul = pow(q->w, 2) + get_dot_product(q_con->vector, q->vector);
	vec = gen_coord(mul * v->x, mul * v->y, mul * v->z);
	free(q_con->vector);
	free(q_con);
	return (vec);
}

static t_vec *orient_vec_util(t_qua *q, t_vec *v)
{
	double	mul;
	t_vec	*vec_one;
	t_vec	*vec_two;
	t_vec	*final;

	mul = 2 * get_dot_product(q->vector, v);
	vec_one = gen_coord(q->vector->x * mul,
						q->vector->y * mul,
						q->vector->z * mul);
	vec_two = orient_vec_util_two(q, v);
	final = add_vectors(vec_one, vec_two);
	free(vec_one);
	free(vec_two);
	return (final);

}

t_vec *orient_vector(t_qua *q, t_vec *v)
{
	double mul;
	t_vec *cross;
	t_vec *vec_one;
	t_vec *vec_two;
	t_vec *vec_new;

	if (q->w == 0.0
		&& q->vector->x == 0.0
		&& q->vector->y == 0.0
		&& q->vector->z == 0.0)
		return (gen_coord(-v->x, -v->y, -v->z));
	vec_one = orient_vec_util(q, v);
	mul = q->w * 2;
	cross = get_cross_product(q->vector, v); //fix if vectors point in opposite directions
	if (cross->x == 0 && cross->y == 0 && cross->z == 0)
		ft_printf("zeroooo\n"); // it shouldn't break anyway if v and q->v are parallel? //TODO: test if opposite v and q->v break THIS SHOULDN'T BREAK
	vec_two = gen_coord(cross->x * mul,
						cross->y * mul,
						cross->z * mul);
	vec_new = add_vectors(vec_one, vec_two);
	free(cross);
	free(vec_one);
	free(vec_two);
	return (vec_new);
}