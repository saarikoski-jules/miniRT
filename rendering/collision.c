#include <stdio.h>//
#include "vec.h"
#include "rt.h"
#include "render.h"
#include <math.h>
#include <stdlib.h>

//TODO: Use defines for out of bounds, behind camera and inside obj

double sp_intersect(t_vec *ray_start, t_vec *ray, t_sp *sp)
{	
	t_vec *len;
	double b;
	double c;

	len = substract_vectors(ray_start, sp->pos);
	if (det_len_vec(len) <= sp->r)
		return (INSIDE_OBJ); //You're inside the circle
	b = 2.0 * get_dot_product(ray, len);
	c = get_dot_product(len, len) - pow(sp->r, 2);
	return (solve_quadratic(1.0, b, c));
}

double pl_intersect(t_vec *orien, t_vec *ray_start, t_vec *pos, t_vec *ray)
{
	//t = ((p0 - l0) dot n) / l dot n
	t_vec *v_pl;
	t_vec *v_n; //Should I make sure here or before calling the function??
	double ln; //ln == 0, ray and plane are parallel
	double pln; //pln == 0, ray is inside line
	double t;

	v_n = set_vec_len(orien, 1); //unnecessary?
	ln = get_dot_product(ray, v_n);
	if (ln == 0)
		return (NO_INTERSECT);
	v_pl = substract_vectors(pos, ray_start);
	pln = get_dot_product(v_pl, v_n);
	t = pln / ln;
	if (t <= 0)
		return (NO_INTERSECT);
	return (t);
}

double sq_intersect(t_vec *ray_start, t_vec *ray, t_sq *sq)
{
	double t;

	t = pl_intersect(sq->orien, ray_start, sq->point1, ray);
	if (t == INFINITY)
		return (INFINITY);
	t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z); //account for different camera pos

	t_vec *intersect = add_vectors(ray_start, point);

	t_vec *edge1 = substract_vectors(sq->point2, sq->point1);
	t_vec *edge2 = substract_vectors(sq->point3, sq->point2); 
	t_vec *edge3 = substract_vectors(sq->point4, sq->point3); 
	t_vec *edge4 = substract_vectors(sq->point1, sq->point4);

	t_vec *P1 = substract_vectors(intersect, sq->point1);
	t_vec *P2 = substract_vectors(intersect, sq->point2);
	t_vec *P3 = substract_vectors(intersect, sq->point3);
	t_vec *P4 = substract_vectors(intersect, sq->point4);

	t_vec *cross1 = get_cross_product(edge1, P1);
	t_vec *cross2 = get_cross_product(edge2, P2);
	t_vec *cross3 = get_cross_product(edge3, P3);
	t_vec *cross4 = get_cross_product(edge4, P4);

	if (get_dot_product(sq->orien, cross1) > 0
		&& get_dot_product(sq->orien, cross2) > 0
		&& get_dot_product(sq->orien, cross3) > 0
		&& get_dot_product(sq->orien, cross4) > 0)
	{
		return (t);
	}
	return (-1);
}

double get_distance(t_vec *point1, t_vec *point2)
{
	double x = pow(point1->x - point2->x, 2);
	double y = pow(point1->y - point2->y, 2);
	double z = pow(point1->z - point2->z, 2);
	double d = sqrt(x + y + z);
	return (d);
}

double get_cy_endcap(t_vec *pos, t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	double	t;
	double	d;
	t_vec	*point;

	t = pl_intersect(cy->orien, ray_start, pos, ray);
	if (t == INFINITY)
		return (INFINITY);
	point = find_point(ray_start, ray, t);
	d = get_distance(point, pos);
	free(point);
	if (d < cy->r)
		return (t);
	return (INFINITY);
}

double get_shaft_intersection_eight(t_vec *ray_start, t_vec *ray, t_cy *cy)
{

	t_vec *O; //check if vector starts inside the cylinder
	t_vec *OC = substract_vectors(ray_start, cy->pos); //vector from vector start point to cylinder centre
	double OC_len = det_len_vec(OC); //distance from vector start to cylinder centre
    // if (OC_len)
	t_vec *OC_u = set_vec_len(OC, 1); //unit vector OC
	t_vec *turn = orient_vector(cy->q, OC_u); //turned unit vector
	t_vec *p = set_vec_len(turn, OC_len); // turned unit vector from ray start point to new cylinder position. Used to be cam_dist

	t_vec *R = orient_vector(cy->q, ray);

    t_vec *O_2d = gen_coord(p->x, p->y, 0);


	double a = pow(R->x, 2) + pow(R->y, 2);
	double b = R->x * p->x * 2 + R->y * p->y * 2;
	double c = pow(p->x, 2) + pow(p->y, 2) - pow(cy->r, 2);

	double t = solve_quadratic(a, b, c);
	if (t <= 0)
		return (INFINITY);
	t_vec *intersection = gen_coord(p->x + t * R->x, p->y + t * R->y, p->z + t * R->z);

	if ((intersection->z > cy->h / 2 || intersection->z < -cy->h / 2)
		|| (intersection->y > cy->r || intersection->y < -cy->r)
		|| (intersection->x > cy->r || intersection->x < -cy->r)) //could do this with the more accurate technique underneath
	{
		return (INFINITY);
	}
	if (det_len_vec(O_2d) <= cy->r
        && p->z <= cy->h / 2
        && p->z >= -cy->h / 2)
	{
        return (-10);
	}
	return (t);
}

double cy_intersect(t_vec *ray_start, t_vec *ray, t_cy *cy)
{
	double t;
	double t1;
	double t2;
	double t3;

	t1 = get_cy_endcap(cy->end1, ray_start, ray, cy);
	t2 = get_cy_endcap(cy->end2, ray_start, ray, cy);
	t3 = get_shaft_intersection_eight(ray_start, ray, cy);
    if (t3 == -10)
        return(-10);
	t = t1;
	if (t2 < t)
	{
		t = t2;
	}
	if (t3 < t)
	{
		t = t3;
	}
	return (t);
}

double tr_intersect(t_vec *ray_start, t_vec *ray, t_tr *tr)
{
	double t = pl_intersect(tr->orien, ray_start, tr->point1, ray);
	if (t == INFINITY)
		return (INFINITY);
	t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z); //account for different camera position
	t_vec *intersect = add_vectors(ray_start, point);
	t_vec *edge1 = substract_vectors(tr->point2, tr->point1); 
	t_vec *edge2 = substract_vectors(tr->point3, tr->point2); 
	t_vec *edge3 = substract_vectors(tr->point1, tr->point3);

	t_vec *P1 = substract_vectors(intersect, tr->point1);
	t_vec *P2 = substract_vectors(intersect, tr->point2);
	t_vec *P3 = substract_vectors(intersect, tr->point3);

	t_vec *cross1 = get_cross_product(edge1, P1);
	t_vec *cross2 = get_cross_product(edge2, P2);
	t_vec *cross3 = get_cross_product(edge3, P3);

	if (get_dot_product(tr->orien, cross1) > 0
		&& get_dot_product(tr->orien, cross2) > 0
		&& get_dot_product(tr->orien, cross3) > 0)
	{
		return (t);
	}
	else
		return (-1.0);
}
