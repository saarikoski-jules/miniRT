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

#include "rt.h"
#include "error.h"

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
