#include "quaternion.h"
#include "libft.h"//
#include "error.h"//
#include <math.h>
#include <stdio.h>//

// t_qua *determine_quaternion_angle(t_vec *orien)
// {
// 	//original orientation vector (0, 0, -1)

// 	t_qua *q;

// 	//orientation must be normalized
// 	t_vec *orien_u;
// 	orien_u = set_vec_len(orien, 1.0);
// 	// orien_u = gen_coord(5, 6, 7);

// 	q = (t_qua *)e_malloc(sizeof(t_qua));
// 	t_vec *base = gen_coord(0, 0, -1);
// 	// t_vec *base = gen_coord(2, 3, 4);

// 	// ft_printf("base: (%f, %f, %f)\norien_u: (%f, %f, %f)\n", base->x, base->y, base->z, orien_u->x, orien_u->y, orien_u->z);
// // (2,3,4) and b = (5,6,7)
// 	t_vec *some_vec = get_cross_product(base, orien_u);
// 	q->vector = set_vec_len(some_vec, 1.0);
// 	//angle in radians
// 	double dot = get_dot_product(base, orien_u); //check if valid angle
// 	q->angle = acos(dot);


// 	return (NULL);
// }

t_qua *determine_quaternion(t_vec *orien)
{
// 	Quaternion q;
// vector a = crossproduct(v1, v2);
// q.xyz = a;

	t_qua *q;

	//orientation must be normalized
	t_vec *orien_u;
	orien_u = set_vec_len(orien, 1.0);
	// orien_u = gen_coord(5, 6, 7);

	q = (t_qua *)e_malloc(sizeof(t_qua));
	t_vec *base = gen_coord(0, 0, -1);
	// t_vec *base = gen_coord(2, 3, 4);

	// ft_printf("base: (%f, %f, %f)\norien_u: (%f, %f, %f)\n", base->x, base->y, base->z, orien_u->x, orien_u->y, orien_u->z);
// (2,3,4) and b = (5,6,7)
	t_vec *some_vec = get_cross_product(base, orien_u);
	q->vector = set_vec_len(some_vec, 1.0);

// q.w = sqrt((v1.Length ^ 2) * (v2.Length ^ 2)) + dotproduct(v1, v2);

	double dot = get_dot_product(base, orien_u); //check if valid angle
	q->w = dot;
		ft_printf("q->vector: (%f, %f, %f), angle: %f\n", q->vector->x, q->vector->y, q->vector->z, q->w);
	//If you want angle out of this, take the acos out of it
	return (q);

}

t_qua *gen_q_conjugate(t_qua *q)
{
	t_qua *q_c;

	q_c = (t_qua*)e_malloc(sizeof(t_qua));
	q_c->w = q->w;
	q_c->vector->x = q->vector->x * -1;
	q_c->vector->y = q->vector->y * -1;
	q_c->vector->z = q->vector->z * -1;
	return (q_c);
}

t_vec *conjugate_vector(t_qua *q, t_vec *v)
{
	t_vec *new;
	t_qua *q_con;

	// q_con = gen_q_conjugate(q);

	double ii = pow(q->vector->x, 2); 
	double jj = pow(q->vector->y, 2);
	double kk = pow(q->vector->z, 2);

	double ij = q->vector->x * q->vector->y;
	double ik = q->vector->x * q->vector->z;
	double jk = q->vector->y * q->vector->z;

	double iw = q->w * q->vector->x;
	double jw = q->w * q->vector->y;
	double kw = q->w * q->vector->z;

	printf("turned vector: (ii: %f, jj: %f, kk: %f)\n", ii, jj, kk);	
	printf("turned vector: (ij: %f, ik: %f, jk: %f)\n", ij, ik, jk);	
	printf("turned vector: (iw: %f, jw: %f, kw: %f)\n", iw, jw, kw);	


/*
	double x1 = (-1 * (jj + kk)) * v->x;
	double x2 = (2 * (jk - kw)) * v->y;
	double x3 = (2 * (ik + jw)) * v->z;

	double y1 = (2 * (ij + kw)) * v->x;
	double y2 = (-1 * (ii + kk)) * v->y;
	double y3 = (2 * (ij - kw)) * v->z;

	double z1 = (2 * (ik - jw)) * v->x;
	double z2 = (2 * (jk + iw)) * v->y;
	double z3 = (-1 * (ii + jj)) * v->z;

	new = gen_coord(x1 + x2 + x3, y1 + y2 + y3, z1 + z2 + z3);

	// new->x = x1 + x2 + x3;
	// new->y = y1 + y2 + y3;
	// new->z = z1 + z2 + z3;
*/

// P2.x = x*(qx*qx+qw*qw-qy*qy- qz*qz) + y*(2*qx*qy- 2*qw*qz) + z*(2*qx*qz+ 2*qw*qy)
// P2.y = x*(2*qw*qz + 2*qx*qy) + y*(qw*qw - qx*qx+ qy*qy - qz*qz)+ z*(-2*qw*qx+ 2*qy*qz)
// P2.z = x*(-2*qw*qy+ 2*qx*qz) + y*(2*qw*qx+ 2*qy*qz)+ z*(qw*qw - qx*qx- qy*qy+ qz*qz)

	new = (t_vec*)e_malloc(sizeof(t_vec));

	// ft_printf("%f\n", ii);

	// double x1 = v->x * (ii + pow(q->w, 2) - jj - kk);
	// double x2 = v->y * ((2 * ij) - (2 * kw));
	// double x3 = v->z * ((2 * ik) + (2 * jw));


	// new->x = x1 + x2 + x3;

	// ft_printf("turned vector: (%f, %f, %f)\n", new->x, new->y, new->z);	
	// ft_printf("turned vector: (%f)\n", new->x);	
	// printf("vec len: %f\n", det_len_vec(new));


    // vprime = 2.0f * dot(u, v) * u
        //   + (s*s - dot(u, u)) * v
        //   + 2.0f * s * cross(u, v);

	//s = w
	//v = vector
	//u = vector part of q

	double tmp = 2 * get_dot_product(q->vector, v);
	printf("%f\n", tmp);
	t_vec *tmp_q = gen_coord(tmp * q->vector->x, tmp * q->vector->y, tmp * q->vector->z);
	double tmp2 = get_dot_product(q->vector, q->vector) * q->w * q->w;



	printf("turned vector: (%f, %f, %f)\n", tmp_q->x, tmp_q->y, tmp_q->z);	
	return (new);
}

// t_qua *set_len_qua(t_qua *q)
// {
// 	t_qua *q_u;

// 	q_u = (t_qua*)e_malloc(sizeof(t_qua));

// }