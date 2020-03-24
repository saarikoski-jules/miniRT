#include "color.h"
#include "vec.h"
#include "libft.h"//
#include "error.h"
#include <stdlib.h>//
#include "render.h"
#include <math.h>

int translate_color(t_color *color)
{
	int rgb;
	rgb = (color->r * pow(16, 4)) + (color->g * pow(16, 2)) + (color->b);
	return (rgb);
}

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


double det_len_vec(t_vec *vector)
{
	double len;

	double x = pow(vector->x, 2);
	double y = pow(vector->y, 2);
	double z = pow(vector->z, 2);

	double sum = x + y + z;
	len = sqrt(sum);
	// ft_printf("(%f, %f, %f)\n(%f, %f, %f)\nsum = %f\nlen = %f\n", vector->x, vector->y, vector->z, x, y, z, sum, len);
	return (len);
}

t_vec *set_vec_len(t_vec *vector, double len)
{
	double vec_len;
	t_vec *new_vec;

	new_vec = (t_vec*)e_malloc(sizeof(t_vec));
	vec_len = det_len_vec(vector);
	new_vec->x = (vector->x / vec_len) * len;
	new_vec->y = (vector->y / vec_len) * len;
	new_vec->z = (vector->z / vec_len) * len;
	// ft_printf("%f\n", det_len_vec(new_vec));
	return (new_vec);
}

int within_grid(t_vec *pos, t_grid *grid)
{
	// ft_printf("min->x: %f, pos->x: %f, max->x: %f\n", grid->up_left->x, pos->x, grid->up_right->x);
	if (pos->x >= grid->up_left->x && pos->x <= grid->up_right->x
	&& pos->y <= grid->up_left->y && pos->y >= grid->down_left->y
	&& pos->z <= grid->up_left->y && pos->y >= grid->down_left->y)
		return (1);
	return (0);
}