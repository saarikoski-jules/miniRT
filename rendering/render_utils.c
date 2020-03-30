#include "color.h"
#include "libft.h"//
#include "error.h"
#include <stdlib.h>//
#include "render.h"
#include <math.h>
#include <stdio.h>

int translate_color(t_color *color)
{
	int rgb;
	rgb = (color->r * pow(16, 4)) + (color->g * pow(16, 2)) + (color->b);
	return (rgb);
}



// int within_grid(t_vec *pos, t_grid *grid)
// {
// 	// ft_printf("min->x: %f, pos->x: %f, max->x: %f\n", grid->up_left->x, pos->x, grid->up_right->x);
// 	if (pos->x >= grid->up_left->x && pos->x <= grid->up_right->x
// 	&& pos->y <= grid->up_left->y && pos->y >= grid->down_left->y
// 	&& pos->z <= grid->up_left->y && pos->y >= grid->down_left->y)
// 		return (1);
// 	return (0);
// }