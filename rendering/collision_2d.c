/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_2d.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 11:39:10 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/01 14:16:38 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "object.h"
#include "render.h"
#include <stdlib.h>

#include "libft.h"//

double	pl_intersect(t_vec *orien, t_vec *ray_start, t_vec *pos, t_vec *ray)
{
	t_vec *v_pl;
	double ln;
	double pln;
	double t;

	ln = get_dot_product(ray, orien);
	if (ln == 0)
		return (NO_INTERSECT);
	v_pl = substract_vectors(pos, ray_start);
	pln = get_dot_product(v_pl, orien);
	free(v_pl);
	t = pln / ln;
	if (t <= 0)
		return (NO_INTERSECT);
	return (t);
}

double	sq_intersect(t_vec *ray_start, t_vec *ray, t_sq *sq)
{
	double	t;
	t_vec	*point;

	// ft_printf("orien: %f, %f, %f\n", sq->orien->x, sq->orien->y, sq->orien->z);
	t = pl_intersect(sq->orien, ray_start, sq->point1, ray);
	if (t == NO_INTERSECT)
		return (NO_INTERSECT);
	// ft_printf("reaches?\n");
	
	point = find_point(ray_start, ray, t);
	if (point_within_line(sq->point1, sq->point2, point, sq->orien) > 0
	&&	point_within_line(sq->point2, sq->point3, point, sq->orien) > 0
	&&	point_within_line(sq->point3, sq->point4, point, sq->orien) > 0
	&&	point_within_line(sq->point4, sq->point1, point, sq->orien) > 0)
	{
		// ft_printf("t %f\n", t);
		free(point);
		return (t);
	}
	// ft_printf("\n");
	free(point);
	return (NO_INTERSECT);
}

double	tr_intersect(t_vec *ray_start, t_vec *ray, t_tr *tr)
{
	double t;
	t_vec *point;
	t = pl_intersect(tr->orien, ray_start, tr->point1, ray);
	if (t == NO_INTERSECT)
		return (NO_INTERSECT);
	point = find_point(ray_start, ray, t);
	if (point_within_line(tr->point1, tr->point2, point, tr->orien) > 0
	&&	point_within_line(tr->point2, tr->point3, point, tr->orien) > 0
	&&	point_within_line(tr->point3, tr->point1, point, tr->orien) > 0)
	{
		free(point);
		return (t);
	}
	free(point);
	return (NO_INTERSECT);
}
