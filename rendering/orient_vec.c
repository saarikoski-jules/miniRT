/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_vec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 17:17:13 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/28 16:08:14 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vec.h"
#include "error.h"
#include <math.h>
#include "libft.h"//


/*
v_new	= q*v*q_con
		= (w,qv)(0,v)(w,-qv) //scalar part results in 0
		= 2(qv⋅v)qv+(w^2−qv⋅qv)v+2w(qv×v)
*/
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

static t_vec	*orient_vec_util_two(t_qua *q, t_vec *v)
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

static t_vec	*orient_vec_util(t_qua *q, t_vec *v)
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

// double uhm(t_qua *q)
// {
// 	t_qua	*q_c;
// 	double	t;

// 	q_c = gen_q_conjugate(q);
		
// 	double x;
// 	double y;
// 	double z;
// 	double w;
// 	double sum;

// 	x = q->vector->x * q_c->vector->x;
// 	y = q->vector->y * q_c->vector->y;
// 	z = q->vector->z * q_c->vector->z;
// 	w = q->w * q_c->w;
// 	sum = x + y + z + w;
	
	
// 	// ft_printf("t: %f\n", sum);	
// 	return (sum);
// }
	// if (sum < 0)
	// {
		// q->vector->y = -q->vector->y;
		// return ();
	// }
	// else
		// return (q);
// }

// (2*dot(qv,v)*qv) + (w^2+dot(-qv,qv)*v) + (2*w*cross(qv,v))
// =2(u⋅v)u+   (s^2−u⋅u)v   +2s(u×v)
t_vec			*orient_vector(t_qua *q, t_vec *v)
{
	double	mul;
	t_vec	*cross;
	t_vec	*vec_one;
	t_vec	*vec_two;
	t_vec	*vec_new;

	if (q->w == 0.0
		&& q->vector->x == 0.0
		&& q->vector->y == 0.0
		&& q->vector->z == 0.0)
		{
			// ft_printf("quat aa\n");
			return (gen_coord(-v->x, -v->y, -v->z));//this may still break
		}
	vec_one = orient_vec_util(q, v);
	mul = q->w * 2;
	cross = get_cross_product(q->vector, v);
	// if (cross->x == 0 && cross->y == 0 && cross->z == 0) //this doesn't actually seem to break
		// ft_printf("zeroooo\n");
	vec_two = gen_coord(cross->x * mul,
						cross->y * mul,
						cross->z * mul);
	vec_new = add_vectors(vec_one, vec_two);
	free(cross);
	free(vec_one);
	free(vec_two);
	// if (vec_new->z > 0)
		// vec_new->y = vec_new->y * -1; //fixish??
	// if (uhm(q) < 0)
	// {
		// vec_new->y = -vec_new->y;
		// vec_new->x = -vec_new->x;
	// }
	return (vec_new);
}