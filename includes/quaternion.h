/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternion.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 19:33:08 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 19:33:36 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "vec.h"

typedef struct	s_qua
{
	double		w;
	t_vec		*vector;
}				t_qua;

t_qua			*determine_quaternion(t_vec *orien, t_vec *base);
t_qua			*gen_q_conjugate(t_qua *q);
t_vec			*orient_vector(t_qua *q, t_vec *v);
t_qua			*gen_unit_quaternion(t_qua *q);
t_qua			*build_unit_q(double w, double x, double y, double z);
void			free_quaternion(t_qua **q);
t_qua			*multiply_quats(t_qua *q1, t_qua *q2);

#endif
