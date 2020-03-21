#include "color.h"
#include "libft.h"//
#include <math.h>

int translate_color(t_color *color)
{
	int rgb;
	rgb = (color->r * pow(16, 4)) + (color->g * pow(16, 2)) + (color->b);
	return (rgb);
}