/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_sp.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 17:06:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 11:48:48 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "collision_utils.h"
#include <math.h>

double	sp_intersect(t_vec *ray_start, t_vec *ray, t_sp *sp)
{
	t_vec	*len;
	double	b;
	double	c;

	len = substract_vectors(ray_start, sp->pos);
	if (det_len_vec(len) <= sp->r)
	{
		free(len);
		return (INSIDE_OBJ);
	}
	b = 2.0 * get_dot_product(ray, len);
	c = get_dot_product(len, len) - pow(sp->r, 2);
	free(len);
	return (solve_quadratic(1.0, b, c));
}
