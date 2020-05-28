/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slerp.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 13:05:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/28 14:16:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "libft.h"//

#include <math.h>

double get_t(t_vec *orien, t_vec *base, t_qua *q)
{
	t_qua	*q_c;
	double	t;

	q_c = gen_q_conjugate(q);
	//cos(omega) = dot(base, orien);
	double omega = acos(get_dot_product(base, orien));
	ft_printf("t: %f\n", omega);
	return (1);
}