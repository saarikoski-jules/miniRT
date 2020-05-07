#include <stdio.h>//
#include "vec.h"
#include "rt.h"
#include "render.h"
#include <math.h>

// double circle(t_rt_scene *scene, t_sp *sp, t_vec *ray, t_vec **n)
double circle(t_rt_scene *scene, t_vec *ray_start, t_vec *ray, t_sp *sp, t_vec **n)
{
	//sphere seems to be a bit too low compared to the square in some cases

	t_vec *ray_u = set_vec_len(ray, 1);

	t_vec *L = substract_vectors(ray_start, sp->pos);
    if (det_len_vec(L) <= sp->dia / 2)
        return (-10); //You're inside the circle
	double dot_L = get_dot_product(L, L);
	double r_pow = pow(sp->dia / 2.0, 2);
	t_vec *dir_u = set_vec_len(ray_u, 1.0);
	double dot_dir_L = get_dot_product(dir_u, L);
	double a = 1.0;
	double b = 2.0 * dot_dir_L;
	double c = dot_L - r_pow;
	double disc = pow(b, 2) - 4 * a * c;
	double d = -1;
	if (disc < 0)
		return (-1.0);
	if (disc > 0)
	{
		double d1 = (((-b) - sqrt(disc)) / 2);
		double d2 = (((-b) + sqrt(disc)) / 2);
		if (d1 < d2)
			d = d1;
		else
			d = d2;
	}
	else if (disc == 0)
	{
		double d3 = (-1 * b) / (2 * a); //should be the same as d = -0.5 * b
		//get normal
		d = d3;
	}
	t_vec *intersect = gen_coord(d * ray_u->x, d * ray_u->y, d * ray_u->z);
	t_vec *i_point = add_vectors(intersect, ray_start);
	t_vec *n_o = substract_vectors(i_point, sp->pos);
	*n = set_vec_len(n_o, 1);
	return (d);
	// return (0);
}

double pl_intersect(t_vec *orien, t_vec *cam_pos, t_vec *pl_pos, t_vec *ray)
{
	//t = ((p0 - l0) dot n) / l dot n
	t_vec *v_pl;
	t_vec *v_n;
	double ln; //ln == 0, ray and plane are parallel
	double pln; //pln == 0, ray is inside line
	double t;

	t_vec *ray_u = set_vec_len(ray, 1); //
	v_n = set_vec_len(orien, 1); //unnecessary?
	ln = get_dot_product(ray_u, v_n); //which one??
	// ln = get_dot_product(ray, v_n); //which one??
	if (ln == 0.0)
		return (INFINITY);//should i use infinity or -1
	v_pl = substract_vectors(pl_pos, cam_pos);
	pln = get_dot_product(v_pl, v_n); //if 0, camera is inside the plane, so plane should be invisible as it is two dimensional
	t = pln / ln;
	if (t <= 0.0) //if t = 0, point is on top of you, so the same outcome as if pln == 0??
		return (INFINITY);
	return (t);
}

// double plane_intersect(t_rt_scene *scene, t_pl *pl, t_vec *ray, t_vec **n)
double plane_intersect(t_rt_scene *scene, t_vec *ray_start, t_vec *ray, t_pl *pl, t_vec **n)
{
	double t;
	double d;
	t_vec *v_point;
	t_vec *v_intersect;

	t = pl_intersect(pl->orien, ray_start, pl->pos, ray);
	if (t == INFINITY)
		return (INFINITY);
	//point of intersection
	v_point = gen_coord(ray->x * t, ray->y * t, ray->z *t); //account for different camera position
	v_intersect = add_vectors(ray_start, v_point); //accounting for camera position
	// d = det_len_vec(v_intersect); //this breaks
	//this should actually be distance
	*n = set_vec_len(pl->orien, 1);
	return (t); //t should be the actual distance as it's calculated with a unit vector
}

// double square(t_rt_scene *scene, t_sq *sq, t_vec *ray, t_vec **n)
double square(t_rt_scene *scene, t_vec *ray_start, t_vec *ray, t_sq *sq, t_vec **n)
{
	t_vec *orien_u;
	double t;

	t_vec *BA = substract_vectors(sq->point2, sq->point1);
	t_vec *CA = substract_vectors(sq->point3, sq->point1);
	t_vec *normal = get_cross_product(BA, CA);
	orien_u = set_vec_len(normal, 1.0);
	// orien_u = set_vec_len(sq->orien, 1); // breaks when the same with camera orientation
	//t may not be distance, is this calculated with unit vector
	t = pl_intersect(sq->orien, ray_start, sq->point1, ray);
	if (t == INFINITY)
		return (INFINITY);
	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *point = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z);//account for different camera pos
	// t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z);//account for different camera pos


	t_vec *intersect = add_vectors(scene->cam->pos, point);

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

	if (get_dot_product(orien_u, cross1) > 0
		&& get_dot_product(orien_u, cross2) > 0
		&& get_dot_product(orien_u, cross3) > 0
		&& get_dot_product(orien_u, cross4) > 0)
	{
		*n = orien_u;
		return (t);
	}
	else
		return (-1.0);
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

double get_cy_endcap(t_vec *pos, t_vec *ray_start, t_vec *ray, t_rt_scene *scene, t_cy *cy)
{
	double t = pl_intersect(cy->orien, ray_start, pos, ray);
	if (t == INFINITY) //if endcap is flat against the camera you won't see it
		return (INFINITY);
	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *point = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z);
	t_vec *intersect = add_vectors(ray_start, point);

	double d = get_distance(intersect, pos);
	if (d < cy->dia / 2.0)
	{
		return (t);
	}
	else
		return (INFINITY);
}

double solve_quadratic(double a, double b, double c)
{
	// printf("b: %f\n", b);
	double disc_end = a * c;
	double disc = pow(b, 2) - disc_end;
	double t;
	double t1 = -1;
	double t2 = -1;
	if (disc < 0)
		return (INFINITY);
	else if (disc > 0)
	{
		t1 = (-b + sqrt(disc)) / a;
		t2 = (-b - sqrt(disc)) / a;
		if (t1 < t2) //might need to change this so it never gets a negative value
			t = t1;
		else
			t = t2;
	}
	else
	{
		t = -b / a;
	}
	// if (t > 0)
		// printf("t: %f\n", t);
	return (t);
}

double get_shaft_intersection_eight(t_camera *cam, t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n)
{

	t_vec *O; //check if vector starts inside the cylinder
	t_vec *OC = substract_vectors(ray_start, cy->pos); //vector from vector start point to cylinder centre
	double OC_len = det_len_vec(OC); //distance from vector start to cylinder centre
    // if (OC_len)
	t_vec *OC_u = set_vec_len(OC, 1); //unit vector OC
	t_vec *turn = orient_vector(cy->q, OC_u); //turned unit vector
	t_vec *p = set_vec_len(turn, OC_len); // turned unit vector from ray start point to new cylinder position. Used to be cam_dist
/*
	// O = add_vectors(cam_dist, cy->pos); // move turned vector by  

	// t_vec *p = substract_vectors(O, cy->pos);
*/

	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *R = orient_vector(cy->q, ray_u);

	t_vec *O_2d = gen_coord(O->x, O->y, 0);
	t_vec *R_2d = gen_coord(R->x, R->y, 0);
	
	double a = pow(R_2d->x, 2) + pow(R_2d->y, 2);
	double b = R_2d->x * p->x + R_2d->y *p->y;
	double c = pow(p->x, 2) + pow(p->y, 2) - pow(cy->r, 2);

	//might need to check if t is negative, though that shouldn't necessarily matter as I'm checking for the range of values anyway.
	double t = solve_quadratic(a, b, c);
	t_vec *intersection = gen_coord(p->x + t * R->x, p->y + t * R->y, p->z + t * R->z);

	if ((intersection->z > cy->h / 2 || intersection->z < -cy->h / 2)
		|| (intersection->y > cy->r || intersection->y < -cy->r)
		|| (intersection->x > cy->r || intersection->x < -cy->r))
	{
		return (INFINITY);
	}
	//Get position along the orien of the cylinder
	t_vec *pos_offset = set_vec_len(cy->orien, intersection->z); //works if this is unit vecs
	t_vec *pos_c = substract_vectors(cy->pos, pos_offset);

	t_vec *i_real = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z);
	t_vec *i_real_c = add_vectors(i_real, ray_start);
	t_vec *normal = substract_vectors(i_real_c, pos_c);
	*n = set_vec_len(normal, 1);//PROBLEM BE HERE BIRCHES
	if ((p->z <= cy->h / 2 && p->z >= -cy->h / 2)
		&& (p->y <= cy->r && p->y >= -cy->r)
		&& (p->x <= cy->r && p->x >= -cy->r))
    {
        printf("(%.10f <= %.10f && %.10f >= %.10f)\n(%.10f <= %.10f && %.10f >= %.10f)\n(%.10f <= %.10f && %.10f >= %.10f)\n", p->z, cy->h / 2, p->z, -cy->h / 2, p->y, cy->r, p->y, -cy->r, p->x, cy->r, p->x, -cy->r);
        printf("ray starting from:\t(%.10f, %.10f, %.10f)\n", ray_start->x, ray_start->y, ray_start->z);
        // printf("ray dir: (%f, %f, %f)\n", ray->x, ray->y, ray->z);
        // printf("cy->pos: (%f, %f, %f)\n\n", cy->pos->x, cy->pos->y, cy->pos->z);
        return (-10); //check if ray starts inside object
    } //Self intersection might not be quite working properly


	return (t);
}

double cylinder(t_rt_scene *scene, t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n)
{
	// t_vec *mov = set_vec_len(cy->orien, cy->h / 2.0);
	// t_vec *pos1 = add_vectors(cy->pos, mov);//account for camera position by turning position into a vector from cam pos
	// t_vec *pos2 = substract_vectors(cy->pos, mov);//account for camera position by turning position into a vector from cam pos
	
	// pos1 = cy->end1;
	// pos2 = cy->end2;
	double t1 = get_cy_endcap(cy->end1, ray_start, ray, scene, cy);
	double t2 = get_cy_endcap(cy->end2, ray_start, ray, scene, cy); //endcaps have stopped working?
	double t3 = get_shaft_intersection_eight(scene->cam, ray_start, ray, cy, n);
    if (t3 == -10)
        return(-10);
	// double t3 = get_shaft_intersection_eight(scene, cy, pos1, ray, pos2, n);
	// t1 = INFINITY;
	// t2 = INFINITY;
	// t3 = INFINITY;

	double t = t1;
	// *n = set_vec_len(substract_vectors(gen_coord(0,0,0), cy->orien), 1);
	if (t2 < t)
	{
		t = t2;
		// *n = set_vec_len(cy->orien, 1);
	}
	if (t3 < t)
	{
		t = t3;
	}
	else
	{
		if (t == t2)
			*n = set_vec_len(cy->orien, 1);
		else if (t == t1)
			*n = set_vec_len(substract_vectors(gen_coord(0,0,0), cy->orien), 1);

		//can also be the invert of this
	}
	return (t);
}

// double triangle(t_rt_scene *scene, t_tr *tr, t_vec *ray, t_vec **n)
double triangle(t_rt_scene *scene, t_vec *ray_start, t_vec *ray, t_tr *tr, t_vec **n)
{
	//calculate normal
	//is the positioning of my triangles strange?
	t_vec *BA = substract_vectors(tr->point2, tr->point1);
	t_vec *CA = substract_vectors(tr->point3, tr->point1);
	t_vec *normal = get_cross_product(BA, CA);
	t_vec *normal_u = set_vec_len(normal, 1.0);

	double t = pl_intersect(normal_u, ray_start, tr->point1, ray);
	if (t == INFINITY)
		return (INFINITY);

	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *point = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z); //account for different camera position
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

	if (get_dot_product(normal_u, cross1) > 0
		&& get_dot_product(normal_u, cross2) > 0
		&& get_dot_product(normal_u, cross3) > 0)
	{
		*n = normal_u;
		return (t); //t is always 10. It should not be? Calculate distance to current intersection point
	}
	else
		return (-1.0);
}
