/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_cy.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 19:11:39 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/13 20:13:33 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "render.h"

double get_cy_endcap(t_vec *pos, t_vec *ray_start, t_vec *ray, t_cy *cy)
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

t_vec *get_turned_ray_start(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	t_vec	*OC;
	t_vec	*OC_u;
	t_vec	*turn;
	t_vec	*p;
	double	OC_len;
	
	OC = substract_vectors(ray_start, cy->pos);
	OC_len = det_len_vec(OC);
    if (OC_len == 0)
	{
		free(OC);
		return (NULL);
	}
	OC_u = set_vec_len(OC, 1);
	turn = orient_vector(cy->q, OC_u);
	p = set_vec_len(turn, OC_len);
	free(OC);
	free(OC_u);
	free(turn);
	return (p);	
}

double validate_cy_intersect(t_vec *p, t_vec *R, double t, t_cy *cy)
{
	t_vec *point;
	double cam_dist;
	double point_dist;

	cam_dist = sqrt(pow(p->x, 2) + pow(p->y, 2));
	if (cam_dist <= cy->r
        && p->z <= cy->h / 2
        && p->z >= -cy->h / 2)
	{
        return (INSIDE_OBJ);
	}
	point = find_point(p, R, t);
	point_dist = sqrt(pow(point->x, 2) + pow(point->y, 2));
	free(point);
	if (point_dist - EPSILON > cy->r ||
		point->z > cy->h / 2 || point->z < -cy->h / 2)
	{
		return (NO_INTERSECT);
	}
	return (t);
}

double get_shaft_intersection(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	t_vec *p;
	t_vec *R;
	double a;
	double b;
	double c;
	double t;

	p = get_turned_ray_start(ray_start, ray, cy);
	if (p == NULL)
		return (INSIDE_OBJ);
	R = orient_vector(cy->q, ray);
	a = pow(R->x, 2) + pow(R->y, 2);
	b = R->x * p->x * 2 + R->y * p->y * 2;
	c = pow(p->x, 2) + pow(p->y, 2) - pow(cy->r, 2);
	t = solve_quadratic(a, b, c);
	if (t <= 0)
		return (NO_INTERSECT);
	t = validate_cy_intersect(p, R, t, cy)
	free(p);
	free(R);
	return (t);
}

double cy_intersect(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	double t;
	double t1;
	double t2;
	double t3;

	t3 = get_shaft_intersection(ray_start, ray, cy);
	if (t3 == INSIDE_OBJ)
		return(INSIDE_OBJ);
	t1 = get_cy_endcap(cy->end1, ray_start, ray, cy);
	t2 = get_cy_endcap(cy->end2, ray_start, ray, cy);
	t = INFINITY;
	if (t1 != NO_INTERSECT)
		t = t1;
	if (t2 != NO_INTERSECT && t2 < t)
		t = t2;
	if ( t3 != NO_INTERSECT && t3 < t)
		t = t3;
	return (t);
}