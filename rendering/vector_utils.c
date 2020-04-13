#include "vec.h"
#include <math.h>
#include "error.h"
#include <stdio.h>//

t_vec *gen_coord(double x, double y, double z)
{
	t_vec *vector;

	vector = (t_vec*)e_malloc(sizeof(t_vec));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vec *determine_vector(t_vec *pos1, t_vec *pos2)
{
	t_vec *vector;

	vector = gen_coord(pos1->x + pos2->x, pos1->y + pos2->y, pos1->z + pos2->z);
	return (vector);
}

t_vec *add_vectors(t_vec *vec1, t_vec *vec2)
{
	t_vec *vector;

	vector = gen_coord(vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z);
	return (vector);
}

t_vec *substract_vectors(t_vec *vec1, t_vec *vec2)
{
	t_vec *vector;

	vector = gen_coord(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
	return (vector);
}

// t_vec *multiply_vectors(t_vec *vec1, t_vec *vec2)
// {
// 	t_vec *vector;

// 	vector = gen_coord(vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z);
// 	return (vector);
// }

t_vec *get_cross_product(t_vec *vec1, t_vec *vec2)
{
	t_vec *vec;

	vec = (t_vec*)e_malloc(sizeof(t_vec));
	// printf("v1: (%f, %f, %f)\n", vec1->x, vec1->y, vec1->z);
	// printf("v2: (%f, %f, %f)\n", vec2->x, vec2->y, vec2->z);
	
	vec->x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
	vec->y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
	vec->z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
	// printf("cross product: (%f, %f, %f)\n", vec->x, vec->y, vec->z);
	return (vec);
}

double get_dot_product(t_vec *vec1, t_vec *vec2)
{
	double x;
	double y;
	double z;
	double sum1;
	double sum;

	x = vec1->x * vec2->x;
	y = vec1->y * vec2->y;
	z = vec1->z * vec2->z;
	// ft_printf("vec1->z %f, vec2->z %f\n", vec1->z, vec2->z);
	// ft_printf("getting dot product: x: %f, y: %f, z: %f\n", x, y, z);
	// printf("%f, %f, %f\n", x, y, z);
	sum = x + y + z;
	// sum = sum1 + y;
	// ft_p
	// printf("sum: %f\n", sum);

	return (sum);
}

double det_len_vec(t_vec *vector) //this may be broken
{
	double len;

	double x = pow(vector->x, 2);
	double y = pow(vector->y, 2);
	double z = pow(vector->z, 2);

	double sum = x + y + z;
	len = sqrt(sum);
	// if (len == 0)
		// error_exit_msg(C_R_INVALID_VEC, E_R_INVALID_VEC);
	// ft_printf("(%f, %f, %f)\n(%f, %f, %f)\nsum = %f\nlen = %f\n", vector->x, vector->y, vector->z, x, y, z, sum, len);
	return (len);
}

t_vec *set_vec_len(t_vec *vector, double len)
{
	double vec_len;
	t_vec *new_vec;

	// ft_printf()
	// ft_printf("set len: (%f, %f, %f)\n", vector->x, vector->y, vector->z);

	new_vec = (t_vec*)e_malloc(sizeof(t_vec));
	vec_len = det_len_vec(vector);
	new_vec->x = (vector->x / vec_len) * len;
	new_vec->y = (vector->y / vec_len) * len;
	new_vec->z = (vector->z / vec_len) * len;
	// ft_printf("%f\n", det_len_vec(new_vec));
	return (new_vec);
}

