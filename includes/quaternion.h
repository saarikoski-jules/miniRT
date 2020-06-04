
#ifndef QUATERNION_H
# define QUATERNION_H

# include "vec.h"

typedef struct	s_qua
{
	double	w;
	t_vec	*vector;
}				t_qua;

// t_qua *determine_quaternion_angle(t_vec *orien);
t_qua *determine_quaternion(t_vec *orien, t_vec *base);
t_qua *determine_quaternion_matrix(t_vec *orien, t_vec *base); //
t_qua *gen_q_conjugate(t_qua *q);
t_vec *orient_vector(t_qua *q, t_vec *v);
t_vec *orient_vector_attempt2(t_qua *q, t_vec *v);//
// t_qua	*gen_unit_quaternion(t_qua *q);
double get_t(t_vec *orien, t_vec *base, t_qua *q);
// double get_t(t_qua *q);


#endif