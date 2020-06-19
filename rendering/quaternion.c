/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 11:33:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/19 12:31:02 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "error.h"
#include <math.h>

static t_qua	*calculate_q_values(t_vec *base_u, t_vec *orien_u, t_vec *axis_u)
{
	double	dot;
	double	angle;
	double	half_sin;
	double	half_cos;
	t_qua	*q_u;

	dot = get_dot_product(base_u, orien_u);
	angle = acos(dot);
	half_sin = sin(0.5 * angle);
	half_cos = cos(0.5 * angle);
	q_u = build_unit_q(half_cos, half_sin * axis_u->x,
								half_sin * axis_u->y,
								half_sin * axis_u->z);
	return(q_u);
}

static t_qua	*parallel_vecs(t_vec *base_u, t_vec *orien_u)
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

#include "libft.h"//

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
	if (axis->x == 0.0 && axis->y == 0.0 && axis->z == 0.0)
	{
		q = parallel_vecs(base_u, orien_u);
	}
	else
	{
		// ft_printf("aa\n");
		axis_u = set_vec_len(axis, 1.0);
		q = calculate_q_values(base_u, orien_u, axis_u);
		free(axis_u);
	}
	free(orien_u);
	free(base_u);
	free(axis);
	// system("leaks a.out");
	// exit(0);
	return (q);
}
