/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 11:57:27 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:11:15 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "color.h"
#include <math.h>

t_color_int	*init_color_int(int r, int g, int b)
{
	t_color_int *color;

	color = (t_color_int *)e_malloc(sizeof(t_color_int));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

void		add_color_and_free(t_color_int **color1, t_color_int **color2)
{
	(*color1)->r += (*color2)->r;
	(*color1)->g += (*color2)->g;
	(*color1)->b += (*color2)->b;
	free(*color2);
	*color2 = NULL;
}

t_color		*gen_color(int r, int g, int b)
{
	t_color *rgb;

	rgb = (t_color *)e_malloc(sizeof(t_color));
	if ((r > 255 || r < 0) &&
		(g > 255 || g < 0) &&
		(b > 255 || b < 0))
		error_exit_msg(C_INVALID_COLOR, E_INVALID_COLOR);
	rgb->r = (unsigned char)r;
	rgb->g = (unsigned char)g;
	rgb->b = (unsigned char)b;
	return (rgb);
}

int			translate_color(t_color *color)
{
	int rgb;

	rgb = (color->r * pow(16, 4)) + (color->g * pow(16, 2)) + (color->b);
	return (rgb);
}
