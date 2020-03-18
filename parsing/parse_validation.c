/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 15:46:03 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 15:46:23 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "rt.h"

void	validate_orien(t_vec *orien)
{
	if (orien->x < -1 || orien->x > 1
	|| orien->y < -1 || orien->y > 1
	|| orien->z < -1 || orien->z > 1)
		error_exit_msg(C_INVALID_ORIEN_VEC, E_INVALID_ORIEN_VEC);
}

void	validate_fov(int fov)
{
	if (fov < 0 || fov > 180)
		error_exit_msg(C_INVALID_FOV, E_INVALID_FOV);
}

void	validate_color(t_color *color)
{
	if ((color->r > 255 || color->r < 0)
	||	(color->g > 255 || color->g < 0)
	||	(color->b > 255 || color->b < 0))
		error_exit_msg(C_INVALID_COLOR, E_INVALID_COLOR);
}
