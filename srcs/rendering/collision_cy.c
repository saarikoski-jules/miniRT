/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_cy.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 19:11:39 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 11:47:08 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include "collision_utils.h"
#include <math.h>

double	get_cy_endcap(t_vec *pos, t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	double	t;
	double	d;
	t_vec	*point;

	t = pl_intersect(cy->orien, ray_start, pos, ray);
	if (t == NO_INTERSECT)
		return (NO_INTERSECT);
	point = find_point(ray_start, ray, t);
	d = get_distance(point, pos);
	free(point);
	if (d < cy->r)
		return (t);
	return (NO_INTERSECT);
}

t_vec	*get_turned_ray_start(t_vec *ray_start, t_cy *cy)
{
	t_vec	*oc;
	t_vec	*oc_u;
	t_vec	*turn;
	t_vec	*p;
	double	oc_len;

	oc = substract_vectors(ray_start, cy->pos);
	oc_len = det_len_vec(oc);
	if (oc_len == 0)
	{
		free(oc);
		return (NULL);
	}
	oc_u = set_vec_len(oc, 1);
	turn = orient_vector(cy->q, oc_u);
	p = set_vec_len(turn, oc_len);
	free(oc);
	free(oc_u);
	free(turn);
	return (p);
}

double	validate_cy_intersect(t_vec *p, t_vec *r, double t, t_cy *cy)
{
	t_vec	*point;
	double	cam_dist;
	double	point_dist;

	cam_dist = sqrt(pow(p->x, 2) + pow(p->y, 2));
	if (cam_dist <= cy->r && p->z <= cy->h / 2 && p->z >= -cy->h / 2)
		return (INSIDE_OBJ);
	point = find_point(p, r, t);
	point_dist = sqrt(pow(point->x, 2) + pow(point->y, 2));
	if (point_dist - EPSILON > cy->r ||
		point->z > cy->h / 2 || point->z < -cy->h / 2)
	{
		free(point);
		return (NO_INTERSECT);
	}
	free(point);
	return (t);
}

double	get_shaft_intersection(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	t_vec	*p;
	t_vec	*r;
	double	b;
	double	c;
	double	t;

	p = get_turned_ray_start(ray_start, cy);
	if (p == NULL)
		return (INSIDE_OBJ);
	r = orient_vector(cy->q, ray);
	b = r->x * p->x * 2 + r->y * p->y * 2;
	c = pow(p->x, 2) + pow(p->y, 2) - pow(cy->r, 2);
	t = solve_quadratic(pow(r->x, 2) + pow(r->y, 2), b, c);
	if (t <= 0)
		t = NO_INTERSECT;
	else
		t = validate_cy_intersect(p, r, t, cy);
	free(p);
	free(r);
	return (t);
}

double	cy_intersect(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	double t;
	double t1;
	double t2;
	double t3;

	t3 = get_shaft_intersection(ray_start, ray, cy);
	if (t3 == INSIDE_OBJ)
		return (INSIDE_OBJ);
	t1 = get_cy_endcap(cy->end1, ray_start, ray, cy);
	t2 = get_cy_endcap(cy->end2, ray_start, ray, cy);
	t = INFINITY;
	if (t1 != NO_INTERSECT)
		t = t1;
	if (t2 != NO_INTERSECT && t2 < t)
		t = t2;
	if (t3 != NO_INTERSECT && t3 < t)
		t = t3;
	if (t == INFINITY)
		t = NO_INTERSECT;
	return (t);
}
