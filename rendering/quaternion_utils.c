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
t_qua *gen_unit_quaternion(t_qua *q)
{
	t_qua *q_u;

	q_u = (t_qua*)e_malloc(sizeof(t_qua));
	double val = pow(q->w, 2) + pow(q->vector->x, 2) + pow(q->vector->y, 2) + pow(q->vector->z, 2);
	double sqrtval = sqrt(val);
	// ft_printf("unit: %f, %f\n", val, sqrtval);

	q_u->w = q->w / sqrtval;
	q_u->vector = gen_coord(q->vector->x / sqrtval, q->vector->y / sqrtval, q->vector->z / sqrtval);
	// q_u->vector->x = q->vector->x / sqrtval;
	// q_u->vector->y = q->vector->y / sqrtval;
	// q_u->vector->z = q->vector->z / sqrtval;

	// ft_printf("quaternion: (%f, %f, %f, %f)\n", q_u->w, q_u->vector->x, q_u->vector->y, q_u->vector->z);

	return (q_u);
}

t_qua *determine_quaternion(t_vec *orien, t_vec *base)
{
// 	Quaternion q;
// vector a = crossproduct(v1, v2);
// q.xyz = a;

	t_qua *q;

	//orientation must be normalized
	t_vec *orien_u;
	orien_u = set_vec_len(orien, 1.0);
	// printf("orien: (%f, %f, %f)\n", orien->x, orien->y, orien->z);
	// printf("orien_u: (%f, %f, %f)\n", orien_u->x, orien_u->y, orien_u->z);
	// orien_u = gen_coord(5, 6, 7);

	q = (t_qua *)e_malloc(sizeof(t_qua));
	// t_vec *base = gen_coord(0, 0, -1);
	// t_vec *base = gen_coord(2, 3, 4);


	// ft_printf("base: (%f, %f, %f)\norien_u: (%f, %f, %f)\n", base->x, base->y, base->z, orien_u->x, orien_u->y, orien_u->z);
// (2,3,4) and b = (5,6,7)

/*

	t_vec *some_vec = get_cross_product(base, orien_u);
	q->vector = set_vec_len(some_vec, 1.0);

// q.w = sqrt((v1.Length ^ 2) * (v2.Length ^ 2)) + dotproduct(v1, v2);

	double dot = get_dot_product(base, orien_u); //check if valid angle
	q->w = dot;
		// ft_printf("q->vector: (%f, %f, %f), angle: %f\n", q->vector->x, q->vector->y, q->vector->z, q->w);
	//If you want angle out of this, take the acos out of it

*/


	/*

	t_vec *cross = get_cross_product(base, orien_u);
	printf("cross: (%f, %f, %f)\n", cross->x, cross->y, cross->z);

	double angle = acos(get_dot_product(base, orien_u) / 2);
	// double angle = acos(get_dot_product(base, orien_u));

	// angle = angle
	printf("half of angle: %f\n", angle);

	// q->vector = gen_coord(sin(angle) * cross->x, sin(angle) * cross->y, sin(angle) * cross->z);
	q->vector = gen_coord(cross->x, cross->y, cross->z);


	q->w = cos(angle);

	*/

//angle = acos(dot_product(v1, v2)); v1 and v2 are normalized

//axis = normalize(cross_product(v1, v2))

    // float half_sin = sin(0.5f * angle);
    // float half_cos = cos(0.5f * angle);
    // return quat(half_cos,
                // half_sin * axis.x,
                // half_sin * axis.y,
                // half_sin * axis.z);


	double dot = get_dot_product(base, orien_u);
	// printf("%f\n", dot);
	double angle = acos(dot);
	t_vec *axis = get_cross_product(base, orien_u);
	if (axis->x == 0 && axis->y == 0 && axis->z == 0)
	{
		if (base->x == orien_u->x && base->y == orien_u->y && base->z == orien_u->z)
		{
			//same direction, no need to turn
			q->w = 1.0;
		}
		else
		{
			q->w = 0.0;
		}
		// printf("bad %f, %f, %f\n", axis->x, axis->y, axis->z);
		q->vector = gen_coord(0.0, 0.0, 0.0);
		return (q);
	}
	t_vec *axis_u = set_vec_len(axis, 1.0);

	// printf("axis: (%.10f, %.10f, %.10f)\n", axis->x, axis->y, axis->z);
	// printf("axis_u: (%.10f, %.10f, %.10f)\n", axis_u->x, axis_u->y, axis_u->z);


	double half_sin = sin(0.5 * angle);
	// printf("sin %f\n", half_sin);
	double half_cos = cos(0.5 * angle);

	q->w = half_cos;
	q->vector = gen_coord(half_sin * axis_u->x, half_sin * axis_u->y, half_sin * axis_u->z);

	// printf("q: %.10f, (%.10f, %.10f, %.10f)\n", q->w, q->vector->x, q->vector->y, q->vector->z);




	t_qua *q_u = gen_unit_quaternion(q);

	// printf("q_u: %.10f, (%.10f, %.10f, %.10f)\n", q_u->w, q_u->vector->x, q_u->vector->y, q_u->vector->z);


	return (q_u);
	// return (NULL);

}

t_qua *gen_q_conjugate(t_qua *q)
{
	t_qua *q_c;

	q_c = (t_qua*)e_malloc(sizeof(t_qua));
	q_c->w = q->w;
	q_c->vector = gen_coord(q->vector->x * (-1), q->vector->y * (-1), q->vector->z * (-1));
	// q_c->vector->x = q->vector->x * (-1);
	// q_c->vector->y = q->vector->y * (-1);
	// q_c->vector->z = q->vector->z * (-1);
	return (q_c);
}


t_vec *orient_vector(t_qua *q, t_vec *v)
{
	// t_vec *new;
	t_qua *q_con;

	// printf("v: (%f, %f, %f)\n", v->x, v->y, v->z);
	if (q->w == 0.0 && q->vector->x == 0.0 && q->vector->y == 0.0 && q->vector->z == 0.0)
		return (gen_coord(-v->x, v->y * -1, v->z * -1));
	q_con = gen_q_conjugate(q);

	// ft_printf("aaa\n");
	// double ii = pow(q->vector->x, 2); 
	// double jj = pow(q->vector->y, 2);
	// double kk = pow(q->vector->z, 2);

	// double ij = q->vector->x * q->vector->y;
	// double ik = q->vector->x * q->vector->z;
	// double jk = q->vector->y * q->vector->z;

	// double iw = q->w * q->vector->x;
	// double jw = q->w * q->vector->y;
	// double kw = q->w * q->vector->z;

	// printf("turned vector: (ii: %f, jj: %f, kk: %f)\n", ii, jj, kk);	
	// printf("turned vector: (ij: %f, ik: %f, jk: %f)\n", ij, ik, jk);	
	// printf("turned vector: (iw: %f, jw: %f, kw: %f)\n", iw, jw, kw);	


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

	// new = (t_vec*)e_malloc(sizeof(t_vec));

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
	//-u = vector part of q_conj

	// ft_printf("q->vec len: %f\n", det_len_vec(q->vector));

	double tmp = 2 * get_dot_product(q->vector, v);
	// printf("dot product uv * 2: %f\n", tmp);

	t_vec *first = gen_coord(q->vector->x * tmp, q->vector->y * tmp, q->vector->z * tmp);

	// printf("First vector: (%f, %f, %f)\n", first->x, first->y, first->z);

	double s2 = pow(q->w, 2);
	// printf("s2: %.10f\n", s2);

	double dotu = get_dot_product(q_con->vector, q->vector);

	// printf("dot product -u . u %.10f\n", dotu);

	double totimes = s2 + dotu;

	// printf("multiply 2nd vector by %.10f\n", totimes);

	t_vec *second = gen_coord(totimes * v->x, totimes * v->y, totimes * v->z);

	// printf("Second vector: (%f, %f, %f)\n", second->x, second->y, second->z);


	double stwo = q->w * 2;

	// printf("w * 2 %f\n", stwo);

	t_vec *cross = get_cross_product(q->vector, v); //fix if vectors point in opposite directions

	// printf("cross product: (%f, %f, %f)\n", cross->x, cross->y, cross->z);

	t_vec *crosstimes = gen_coord(cross->x * stwo, cross->y * stwo, cross->z * stwo);

	// printf("cross product times s * 2: (%f, %f, %f)\n", crosstimes->x, crosstimes->y, crosstimes->z);

	t_vec *semifinal = add_vectors(first, second);
	t_vec *final = add_vectors(semifinal, crosstimes);

	// printf("final: (%f, %f, %f)\n", final->x, final->y, final->z);


	// t_vec *tmp_q = gen_coord(tmp * q->vector->x, tmp * q->vector->y, tmp * q->vector->z);
	// double tmp2 = pow(q->w, 2) - get_dot_product(q->vector, q_con->vector);
	// t_vec *tmp_v = gen_coord(tmp2 * v->x, tmp2 * v->y, tmp2 * v->z);

	// t_vec *add = add_vectors(tmp_q, tmp_v);

	// t_vec *cross = get_cross_product(q->vector, v);
	// t_vec *final = gen_coord(cross->x * q->w * 2.0, cross->y * q->w * 2.0, cross->z * q->w * 2.0);

	// t_vec *end = add_vectors(add, final);

	// printf("turned vector: (%.10f, %.10f, %.10f)\n", tmp_q->x, tmp_q->y, tmp_q->z);	
	// printf("turned vector: (%.10f, %.10f, %.10f)\n", tmp_v->x, tmp_v->y, tmp_v->z);
	// printf("turned vector: (%.10f, %.10f, %.10f)\n", add->x, add->y, add->z);
	// printf("turned vector: (%.10f, %.10f, %.10f)\n", cross->x, cross->y, cross->z);
	// printf("turned vector: (%.10f, %.10f, %.10f)\n", final->x, final->y, final->z);
	// printf("turned vector: (%.10f, %.10f, %.10f)\n", end->x, end->y, end->z);


	return (final);
}

// t_qua *set_len_qua(t_qua *q)
// {
// 	t_qua *q_u;

// 	q_u = (t_qua*)e_malloc(sizeof(t_qua));

// }