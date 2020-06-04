/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 11:33:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/04 16:56:09 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */




#include "quaternion.h"
#include "error.h"
#include <math.h>
#include "libft.h"//


// TODO: Quats break at 0,0,1 the y axis flips when x = 0 ???
// TODO: Up seems to tilt rather than turn
// TODO: Y AXIS IS ENTIRELY FLIPPED BEHIND THE NORMAL ORIENTATION

// TODO: Y axis tilts when manipulating the y orientation coord. 


t_qua	*gen_unit_quaternion(t_qua *q)
{
	t_qua	*q_u;
	double	val;
	double	len;

	val = pow(q->w, 2) +
				pow(q->vector->x, 2) +
				pow(q->vector->y, 2) +
				pow(q->vector->z, 2);
	len = sqrt(val);
	// if (len == 1.0)
		// return (q);
	q_u = (t_qua*)e_malloc(sizeof(t_qua));
	q_u->w = q->w / len;
	q_u->vector = gen_coord(q->vector->x / len,
							q->vector->y / len,
							q->vector->z / len);
	return (q_u);
}

static t_qua	*calculate_q_values(t_vec *base_u, t_vec *orien_u, t_vec *axis_u)
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

static t_qua	*parallel_vecs(t_vec *base_u, t_vec *orien_u)
{
	t_qua *q;

	q = (t_qua *)e_malloc(sizeof(t_qua));
	if (base_u->x == orien_u->x && base_u->y == orien_u->y && base_u->z == orien_u->z)
		q->w = 1.0;
	else
		q->w = 0.0; //this is wrong
	ft_printf("quat: %f\n", q->w);
	q->vector = gen_coord(0.0, 0.0, 0.0);
	return (q);
}

// t_qua *uhm(t_qua *q)
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
	
	
// 		ft_printf("t: %f\n", sum);
// 	if (sum < 0)
// 	{
// 		// q->vector->y = -q->vector->y;
// 		return (q);
// 	}
// 	else
// 		return (q);
// }

t_qua			*determine_quaternion(t_vec *orien, t_vec *base)
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
	ft_printf("axis: (%f, %f, %f)\n", axis->x, axis->y, axis->z);
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
	// ft_printf("q before: %f, (%f, %f, %f)\n", q->w, q->vector->x, q->vector->y, q->vector->z);
	// q = uhm(q);
	// ft_printf("q after: %f, (%f, %f, %f)\n", q->w, q->vector->x, q->vector->y, q->vector->z);
	return (q);
}


// Quaternion q;
// double trace = R.x + U.y + F.z;
// if (trace > 0.0) {
//   double s = 0.5 / sqrt(trace + 1.0);
//   q.w = 0.25 / s;
//   q.x = (U.z - F.y) * s;
//   q.y = (F.x - R.z) * s;
//   q.z = (R.y - U.x) * s;
// } else {
//   if (R.x > U.y && R.x > F.z) {
//     double s = 2.0 * sqrt(1.0 + R.x - U.y - F.z);
//     q.w = (U.z - F.y) / s;
//     q.x = 0.25 * s;
//     q.y = (U.x + R.y) / s;
//     q.z = (F.x + R.z) / s;
//   } else if (U.y > F.z) {
//     double s = 2.0 * sqrt(1.0 + U.y - R.x - F.z);
//     q.w = (F.x - R.z) / s;
//     q.x = (U.x + R.y) / s;
//     q.y = 0.25 * s;
//     q.z = (F.y + U.z) / s;
//   } else {
//     double s = 2.0 * sqrt(1.0 + F.z - R.x - U.y);
//     q.w = (R.y - U.x) / s;
//     q.x = (F.x + R.z) / s;
//     q.y = (F.y + U.z) / s;
//     q.z = 0.25 * s;
//   }
// }

t_qua	*determine_quaternion_matrix(t_vec *orien, t_vec *base)
{
	//F = orien
	t_vec *up = gen_coord(0, 1, 0);
	t_vec *R = get_cross_product(orien, up);
	t_vec *R_u = set_vec_len(R, 1.0);
	t_vec *U = get_cross_product(R_u, orien);
	t_qua *q;
	q = (t_qua *)e_malloc(sizeof(t_qua));
	free(R);
	R = NULL;
	double trace = R_u->x + U->y + orien->z;
		// ft_printf("here\n");
	if (trace > 0.0)
	{
		ft_printf("trace == %f\n", trace);
		double s = 0.5 / sqrt(trace + 1.0);
  		q->w = 0.25 / s;
		q->vector = gen_coord((U->z - orien->y) * s,
								(orien->x - R_u->z) * s,
								(R_u->y - U->x) * s);		
	}
	else 
	{
		ft_printf("trace is %f\n", trace);
		if (R_u->x > U->y && R_u->x > orien->z) {
			double s = 2.0 * sqrt(1.0 + R_u->x - U->y - orien->z);
			q->w = (U->z - orien->y) / s;
	
			q->vector = gen_coord(0.25 * s,
								(U->x + R->y) / s,
								(orien->x + R_u->z) / s);		



			// q.x = 0.25 * s;
			// q.y = (U.x + R.y) / s;
			// q.z = (orien->x + R.z) / s;
		} else if (U->y > orien->z) {
			double s = 2.0 * sqrt(1.0 + U->y - R_u->x - orien->z);
			q->w = (orien->x - R_u->z) / s;

			q->vector = gen_coord((U->x + R->y) / 2,
								0.25 * s,
								(orien->y + U->y) / s);		


			// q.x = (U.x + R.y) / s;
			// q.y = 0.25 * s;
			// q.z = (orien->y + U.z) / s;
		} else {
			double s = 2.0 * sqrt(1.0 + orien->z - R_u->x - U->y);
			q->w = (R_u->y - U->x) / s;

			q->vector = gen_coord((orien->x + R_u->z) / s,
								(orien->y + U->z) / s,
								0.25 * s);	



			// q.x = (orien->x + R.z) / s;
			// q.y = (F.y + U.z) / s;
			// q.z = 0.25 * s;
  		}	
	}
	return (q);
}




