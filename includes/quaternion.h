
#ifndef QUATERNION_H
# define QUATERNION_H

# include "vec.h"

typedef struct	s_qua
{
	double	w;
	t_vec	*vector;
}				t_qua;

// t_qua *determine_quaternion_angle(t_vec *orien);
t_qua *determine_quaternion(t_vec *orien);
t_qua *gen_q_conjugate(t_qua *q);
t_vec *orient_vector(t_qua *q, t_vec *v);


#endif