#include "vec.h"
#include "render.h"
#include <math.h>
#include <stdlib.h>

// TODO: Use defines for out of bounds, behind camera and inside obj
// TODO: multiple cameras
// TODO: Save pixels to img and use put_img instead of put_pixel
// TODO: --save to bmp
// TODO: keybinds for rotating cameras 

double sp_intersect(t_vec *ray_start, t_vec *ray, t_sp *sp)
{	
	t_vec	*len;
	double	b;
	double	c;

	len = substract_vectors(ray_start, sp->pos);
	if (det_len_vec(len) <= sp->r)
	{	
		free(len);
		return (INSIDE_OBJ); //You're inside the circle
	}
	b = 2.0 * get_dot_product(ray, len);
	c = get_dot_product(len, len) - pow(sp->r, 2);
	free(len);
	return (solve_quadratic(1.0, b, c));
}
