#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "quaternion.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//

#define DIST 1 //choose: determine camera distance from grid
#define FOV_VERT 60 //choose: determine vertical fov
//choose: default rotation of camera, should be changeable.


// 	// ☺

double circle(t_rt_scene *scene, t_sp *sp, t_vec *ray)
{
	t_vec *L = substract_vectors(scene->cam->pos, sp->pos);
	double dot_L = get_dot_product(L, L);
	double r_pow = pow(sp->dia / 2.0, 2);
	t_vec *dir_u = set_vec_len(ray, 1.0);
	double dot_dir_L = get_dot_product(dir_u, L);
	double a = 1.0;
	double b = 2.0 * dot_dir_L;
	double c = dot_L - r_pow;
	double disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (-1.0);
	if (disc > 0)
	{
		double d1 = (((-b) - sqrt(disc)) / 2);
		double d2 = (((-b) + sqrt(disc)) / 2);
		if (d1 < d2)
			return (d1);
		else
			return (d2);
	}
	else if (disc == 0)
	{
		double d = (-1 * b) / (2 * a); //should be the same as d = -0.5 * b
		return (d);
	}
	return (0);
}

double pl_intersect(t_vec *orien, t_vec *cam_pos, t_vec *pl_pos, t_vec *ray)
{
	//t = ((p0 - l0) dot n) / l dot n
	t_vec *v_pl;
	t_vec *v_n;
	double ln; //ln == 0, ray and plane are parallel
	double pln; //pln == 0, ray is inside line
	double t;

	v_n = set_vec_len(orien, 1); //unnecessary?
	ln = get_dot_product(ray, v_n); //which one??
	if (ln == 0.0)
		return (INFINITY);//should i use infinity or -1
	v_pl = substract_vectors(pl_pos, cam_pos);
	pln = get_dot_product(v_pl, v_n); //if 0, camera is inside the plane, so plane should be invisible as it is two dimensional
	t = pln / ln;
	if (t <= 0.0) //if t = 0, point is on top of you, so the same outcome as if pln == 0??
		return (INFINITY);
	return (t);
}

double plane_intersect(t_rt_scene *scene, t_pl *pl, t_vec *ray)
{

	double t;
	double d;
	t_vec *v_point;
	t_vec *v_intersect;

	t = pl_intersect(pl->orien, scene->cam->pos, pl->pos, ray);
	if (t == INFINITY)
		return (INFINITY);
	//point of intersection
	v_point = gen_coord(ray->x * t, ray->y * t, ray->z *t); //account for different camera position
	v_intersect = add_vectors(scene->cam->pos, v_point); //accounting for camera position
	// d = det_len_vec(v_intersect); //this breaks
	//this should actually be distance
	return (t); //t should be the actual distance as it's calculated with a unit vector
}


// Ray : P(t) = O + V * t
//  // Cylinder [O, D, r].
//  // point Q on cylinder if ((Q - O) x D)^2 = r^2
//  //// Cylinder [A, B, r].
//  // Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
//  // expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
//  // equation in the form (X + t * Y)^2 = d
//  // where : 
//  //  X = (O - A) x (B - A)
//  //  Y = V x (B - A)
//  //  d = r^2 * (B - A)^2
//  // expand the equation :
//  // t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
//  // => second order equation in the form : a*t^2 + b*t + c = 0 where
//  // a = (Y . Y)
//  // b = 2 * (X . Y)
//  // c = (X . X) - d
//  //--------------------------------------------------------------------------
//  Vector AB = (B - A);
//  Vector AO = (O - A);
//  Vector AOxAB = (AO ^ AB); 
//  // cross product
//  Vector VxAB  = (V ^ AB); 
//  // cross product
//  float  ab2   = (AB * AB); 
//  // dot product
//  float a      = (VxAB * VxAB); 
//  // dot product
//  float b      = 2 * (VxAB * AOxAB); 
//  // dot product
//  float c      = (AOxAB * AOxAB) - (r*r * ab2);
//  // solve second order equation : 
//  a*t^2 + b*t + c = 0

// double 	cylinder(t_rt_scene *scene, t_obj *cy, t_vec *ray)
// {
// 	t_vec *orien_u = set_vec_len(cy->type.cy->orien, 1.0);
// 	t_vec *cylinder = substract_vectors(cy->type.cy->pos, orien_u);
// 	ft_printf("cylinder: (%f, %f, %f)\n", cylinder->x, cylinder->y, cylinder->z);

// }

double square(t_rt_scene *scene, t_sq *sq, t_vec *ray)
{
	t_vec *orien_u;
	double t;

	orien_u = set_vec_len(sq->orien, 1);
	//t may not be distance, is this calculated with unit vector
	t = pl_intersect(sq->orien, scene->cam->pos, sq->point1, ray);
	if (t == INFINITY)
		return (INFINITY);

	t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z);//account for different camera pos

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

	// t_qua *turn determine_quaternion(ray, gen_coord(0,0,-1));

	if (get_dot_product(orien_u, cross1) > 0
		&& get_dot_product(orien_u, cross2) > 0
		&& get_dot_product(orien_u, cross3) > 0
		&& get_dot_product(orien_u, cross4) > 0)
	{
		// ft_printf("t: %f\n", t);
		// printf("ray:\t(%f, %f, %f)\n", ray->x, ray->y, ray->z);
		// t_vec *v_intersect = add_vectors(scene->cam->pos, point);//accounting for different camera position
		// printf("point:\t(%f, %f, %f)\n", point->x, point->y, point->z);
		// printf("intersect:\t(%f, %f, %f)\n", intersect->x, intersect->y, intersect->z);
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

double get_cy_endcap(t_vec *pos, t_vec *ray, t_rt_scene *scene, t_cy *cy)
{
	double t = pl_intersect(cy->orien, scene->cam->pos, pos, ray);
	if (t == INFINITY)
		return (INFINITY);
	t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z);
	t_vec *intersect = add_vectors(scene->cam->pos, point);

	double d = get_distance(intersect, pos);
	if (d < cy->dia / 2.0)
	{
		// ft_printf("d: %f\n", d);
		return (t);
	}
	else
		return (INFINITY);
}

double get_shaft_intersection(t_rt_scene *scene, t_cy *cy,
	t_vec *pos1, t_vec *ray, t_vec *pos2)
{

	//moving the positions here is not right at all as it's not enough that the direction vectors turn, but everything has to turn in relation to each other.


	//turn ray by
	t_vec *base = gen_coord(0, 0, -1);
	t_qua *turn = determine_quaternion(base, cy->orien);//

	//move ray origin by
	t_vec *mov = substract_vectors(scene->cam->pos, pos1);
	// printf("position of endcap centre: (%f, %f, %f)\nposition of camera (%f, %f, %f)\n", pos1->x, pos1->y, pos1->z, scene->cam->pos->x, scene->cam->pos->y, scene->cam->pos->z);
	// printf("mov: (%f, %f, %f)\n", mov->x, mov->y, mov->z);



/*
//	TESTING ------------------------------

	t_vec *test = orient_vector(q, cy->orien);//
	t_vec *check = set_vec_len(base, 1);
	ft_printf("Is this\t\t\t(%f, %f, %f)\n", test->x, test->y, test->z);
	ft_printf("Should be this\t(%f, %f, %f)\n", check->x, check->y, check->z);
//	--------------------------------------
*/

	//Turn and move ray based on the movement of the cylinder

	//New ray start position
	t_vec *ray_start = add_vectors(scene->cam->pos, mov);
	
	
	//length of vector
	double len_ray_start = det_len_vec(substract_vectors(ray_start, scene->cam->pos));

	//direction where the new starting position of ray will be

	t_vec *ray_start_two = orient_vector(turn, ray_start);

	//final position of the ray's starting point
	t_vec *final_ray_start = set_vec_len(ray_start_two, len_ray_start);



	//move ray start position by quaternion

	// printf("ray len: %f\nmoved ray origin (%f, %f, %f)\n", len_ray_start, ray_start->x, ray_start->y, ray_start->z);

	//New ray direction
	t_vec *ray_direction = orient_vector(turn, ray);
	// printf("original ray direction (%f, %f, %f)\n", ray->x, ray->y, ray->z);
	// printf("turned ray direction (%f, %f, %f)\n", ray_direction->x, ray_direction->y, ray_direction->z);



	//cast ray to xy plane, so drop z coord
	//find intersection with circle drawn onto xy plane at the start of the cylinder, so at origin (0,0) with r cy->dia / 2


	//solve a quadratic for intersections


	t_vec *ray_start_2d = gen_coord(final_ray_start->x, final_ray_start->y, 0);
	t_vec *ray_dir_2d = gen_coord(ray_direction->x, ray_direction->y, 0);

	// printf("start: (%f, %f, %f), dir: (%f, %f, %f)\n", ray_start_2d->x, ray_start_2d->y, ray_start_2d->z, ray_dir_2d->x, ray_dir_2d->y, ray_dir_2d->z);
	t_vec *O = gen_coord(0,0,0);

	// printf("ray start: (%f, %f, %f)\n", final_ray_start->x,final_ray_start-> y,final_ray_start->z);
	// printf("ray start 2d: (%f, %f, %f)\n", ray_start_2d->x,ray_start_2d-> y,ray_start_2d->z);



/*
	ATTEMPT 1 AT A QUADRATIC

	//All in 2D

	//b = 2 (k dot (A - O))
	//a = pow(k, 2)
	//c = pow((A - O), 2) - pow(r, 2)

	//k = ray_direction xy
	//A = ray_start xy
	//O = (0, 0)
	//r = cy->dia / 2

	t_vec *AO = substract_vectors(ray_start_2d, O);
	double b = 2 * get_dot_product(ray_dir_2d, AO);
	double a = get_dot_product(ray_dir_2d, ray_dir_2d);
	double c = get_dot_product(AO, AO) - pow(cy->dia * 0.5, 2);


	//solve quadratic

	double disc = pow(b, 2) - 4 * a * c;
	// printf("%f = (%f)pow2 - 4 * %f * %f\n\n", disc, b, a, c);
	// if (disc >= 0)

*/

// ATTEMPT 2 AT A QUADRATIC

	//gives the exact same result as previus calculation

	t_vec *ray_dir_2d_u = set_vec_len(ray_dir_2d, 1);

	//c = position of the circle centre = (0,0,0) = O
	//d = position vector of start point of ray = ray_start_2d
	//n = unit direction vector of ray = ray_dir_2d_u
	//r = radius of circle = cy->dia / 2

	t_vec *CD = substract_vectors(O, ray_start_2d);

	double b = get_dot_product(CD, ray_dir_2d_u);
	double a = 1.0;
	double c = get_dot_product(ray_start_2d, ray_start_2d) - pow(cy->dia / 2.0, 2);

	double disc = pow(b, 2) - 4 * c;

	//check against the height of the cylinder
	

	double t;
	if (disc > 0)
	{
		double t_top = -b + sqrt(disc);
		t = t_top / 2;
		if (t < 0)
			return (INFINITY);
		// t_vec *r = gen_coord(t * ray->x, t * ray->y, t * ray->z);
		// t_vec intersect = add_vectors(scene->cam->pos, r);
		// if ()
	}
	if (disc >= 0)
		return (1);
	else
		return (INFINITY);

	// return (1);
}

double get_shaft_intersection_two(t_rt_scene *scene, t_cy
		*cy, t_vec *pos1, t_vec *ray, t_vec *pos2)
{

	// (((P + V*t) - A) x (B - A))^2 = r^2 * ((B - A) . (B - A))
	// vector (or dot product with itself?) =	scalar		??
	// solve for t



//------------------------------------------------------------------
// Ray : P(t) = O + V * t
// Cylinder [O, D, r].
// point Q on cylinder if ((Q - O) x D)^2 = r^2
//
// Cylinder [A, B, r].
// Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
// expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
// equation in the form (X + t * Y)^2 = d
// where : 
//  X = (O - A) x (B - A)
//  Y = V x (B - A)
//  d = r^2 * (B - A)^2
// expand the equation :
// t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
// => second order equation in the form : a*t^2 + b*t + c = 0 where
// a = (Y . Y)
// b = 2 * (X . Y)
// c = (X . X) - d
//-----------------------------------------------------------

// B = Endpoint of cylinder
// A = Startpoint of cylinder
// O = Ray start point
// V = Ray direction

// /*
t_vec *AB = substract_vectors(pos2, pos1);
// Vector AB = (B - A);
t_vec *AO = substract_vectors(scene->cam->pos, pos1);
// Vector AO = (O - A);
t_vec *AOxAB = get_cross_product(AO, AB);
// Vector AOxAB = (AO ^ AB); 
// cross product
t_vec *VxAB = get_cross_product(ray, AB);
// Vector VxAB  = (V ^ AB); 
// cross product
double ab2 = get_dot_product(AB, AB);
// double  ab2   = (AB * AB); 
// dot product
double a = get_dot_product(VxAB, VxAB);
// double a      = (VxAB * VxAB);
// dot product
double b = 2 * get_dot_product(VxAB, AOxAB);
// double b      = 2 * (VxAB * AOxAB);
// dot product
double c2 = (pow(cy->dia / 2, 2) * a * b * 2);
double c = get_dot_product(AOxAB, AOxAB) - c2;
// double c      = (AOxAB * AOxAB) - (r*r * ab2);
// solve second order equation : a*t^2 + b*t + c = 0

double disc = pow(b, 2) - (4 * a * c);
printf("%f = pow(%f, 2) - (4 * %f * %f)\n", disc, b, a, c);
if (disc >= 0)
	return (1);
else
	return (INFINITY);

// */


}

double get_shaft_intersection_three(t_rt_scene *scene, t_cy *cy,
	t_vec *pos1, t_vec *ray, t_vec *pos2)
{
	//ray = at + b
	//a = ray, b = scene->cam->pos 
	//cylinder = gs + h
	//g = AB, h = A

	t_vec *g = substract_vectors(pos2, pos1);

	//D is distance, cy->dia / 2

	// if |g| == 0, death

	double len_g = det_len_vec(g);
	if (len_g == 0)
	{
		printf("FAAAIL");
		return (INFINITY);
	}
	//c = g x (b - h) / |g|
	
	t_vec *bh = substract_vectors(scene->cam->pos, pos1);
	t_vec *c1 = get_cross_product(g, bh);
	t_vec *c = gen_coord(c1->x / len_g, c1->y / len_g, c1->z / len_g);

	//k = (g x a) / |g|

	t_vec *k1 = get_cross_product(g, ray);
	t_vec *k = gen_coord(k1->x / len_g, k1->y / len_g, k1->z / len_g);

	//if |k| == 0, death

	double k_len = det_len_vec(k);
	if (k_len == 0)
	{
		printf("destruction\n");
		return (0);
	}

	//d = 4 * (k * c)^2 - 4|k|^2*(|c|^2 * D^2)

	double c_len = det_len_vec(c);
	double d1 = pow(c_len, 2) * pow(cy->dia / 2, 2);
	double d2 = 4 * pow(k_len, 2) * d1;
	double kc = get_dot_product(k, c);
	double d = 4 * pow(kc, 2) - d2;

	//if d >= 0, there's an answer

	if (d >= 0)
		return (1);
	else
		return (INFINITY);

	//t = (-2 * (k * c) +- sqrt(d)) / 2 |k|^2

	//plug t into ray and you get position of intersection

}


double get_shaft_intersection_four(t_rt_scene *scene, t_cy *cy,
	t_vec *pos1, t_vec *ray, t_vec *pos2)
{
	// return (INFINITY);
	// ft_printf("cy info:\n\tdiameter: %f\n\tr: %f\n\tend1: (%f, %f, %f)\n\tend2: (%f, %f, %f)\n", cy->dia, cy->r, cy->end1->x, cy->end1->y, cy->end1->z, cy->end2->x, cy->end2->y, cy->end2->z);

	//move and turn ray according to the movement of the cylinder first

	//camera origin (MOVE AND TURN TO CORRECT FOR POSITIONING)
	t_vec *O = scene->cam->pos;
	
	//ray direction (TURN ACCORDING TO OBJECT TURN)
	t_vec *R = ray;

	//get two dimensional start point and ray
	t_vec *O_2d = gen_coord(O->x, O->y, 0);
	t_vec *R_2d = gen_coord(R->x, R->y, 0);

	//get vector between ray origin and circle centre
	t_vec *p = substract_vectors(O, cy->end1);

	//Find intersection between 2d ray and circle at (0,0,0) with radius cy->r 
	
	double a = pow(R_2d->x, 2) + pow(R_2d->y, 2);
	double b = R_2d->x * p->x + R_2d->y *p->y;
	double c = pow(p->x, 2) + pow(p->y, 2) - pow(cy->r, 2);

	// double s = R_2d->x * p->x;
	// double t = R_2d->y * p->y;
	double disc_end = a * c;
	double disc = pow(b, 2) - disc_end;
	// printf("a: %f, b: %f, c: %f\n", a, b, c);
	// printf("s: %f, t: %f\n", s, t);
	// printf("%f = %f^2 - %f * %f\n", disc, b, a, c);
	
	double t;
	if (disc < 0)
		return (INFINITY);
	else if (disc > 0)
	{
		double t1 = -b + sqrt(disc) / a;
		double t2 = -b - sqrt(disc) / a;
		if (t1 < t2)
			t = t1;
		else
			t = t2;
	}
	else
	{
		t = -b / a;
	}
	
	//determine z coordinate of intersection
	// double z = p->z + t * ray->z;

	t_vec *point = gen_coord(p->x + t * ray->x, p->y + t * ray->y, p->z + t * ray->z);

	// t_vec *halp = add_vectors(ray, scene->cam->pos);
	// t_vec *point = gen_coord(t * halp->x, t * halp->y, t * halp->z);
	// printf("point (%f, %f, %f), end1: (%f, %f, %f), end2 (%f, %f, %f)\n", point->x, point->y, point->z, cy->end1->x, cy->end1->y, cy->end1->z, cy->end2->x, cy->end2->y, cy->end2->z);
	//change to work for any position and rotation

	// printf("%f > %f || %f < %f\n", point->z, cy->end2->z, point->z, cy->end1->z);

	// if (point->z > cy->end2->z || point->z < cy->end1->z)
	if (point->z < cy->end2->z || point->z > cy->end1->z)
		return (INFINITY);

	//get and return distance from camera (or t?)
	return (t);
}

double cylinder(t_rt_scene *scene, t_cy *cy, t_vec *ray)
{

	//generate point half the height in the direction of orientation
	t_vec *mov = set_vec_len(cy->orien, cy->h / 2.0);
	t_vec *pos1 = add_vectors(cy->pos, mov);//account for camera position by turning position into a vector from cam pos
	t_vec *pos2 = substract_vectors(cy->pos, mov);//account for camera position by turning position into a vector from cam pos
	
	double t1 = get_cy_endcap(pos1, ray, scene, cy);
	double t2 = get_cy_endcap(pos2, ray, scene, cy);
	// double t2 = pl_intersect(cy->orien, scene->cam->pos, pos2, ray);


	// t1 = INFINITY;
	// t2 = INFINITY;


	//move everything so that pos2 is at origo
	// printf("hi\n");
	// double t3 = get_shaft_intersection(scene, cy, pos1, ray, pos2);
	// double t3 = get_shaft_intersection_two(scene, cy, pos1, ray, pos2);
	// double t3 = get_shaft_intersection_three(scene, cy, pos1, ray, pos2);
	double t3 = get_shaft_intersection_four(scene, cy, pos1, ray, pos2);


	// ft_printf("t1 %f, t2 %f\n", t1, t2);
	// if (t1 < t2 && t1 != -1.0)
		// return (t1);
	// else if (t2 < t1 && t2 != -1.0)
		// return (t2);
	// else

	double t = t1;
	if (t2 < t)
		t = t2;
	if (t3 < t)
		t = t3;

	return (t);

	// if (t1 < t2)
		// return (t1);
	// if (t2 <= t1 && t2 != INFINITY)
		// return (t2);
	// return (-1.0);

	// t_vec *point2 = gen_coord(t2 * ray->x, t2 * ray->y, t2 * ray->z);
	// t_vec *intersect2 = add_vectors(scene->cam->pos, point2);

	// double t = -1.0;

	// double d2 = get_distance(intersect2, pos2);
	// double d2 = get_distance(intersect, cy->pos);
	// printf("d: %f < %f\n", d2, cy->dia);
	// if (d1 < cy->dia / 2.0)
		// t = t1;
	// if (d2 < cy->dia / 2.0 && d2 < d1)
		// t = t2;
	// return (t);

	// t_vec *sub = substract_vectors(intersect, cy->pos);
	// det_len_vec(sub);
}

double triangle(t_rt_scene *scene, t_tr *tr, t_vec *ray)
{
	//calculate normal
	//is the positioning of my triangles strange?
	t_vec *BA = substract_vectors(tr->point2, tr->point1);
	t_vec *CA = substract_vectors(tr->point3, tr->point1);
	t_vec *normal = get_cross_product(BA, CA);
	t_vec *normal_u = set_vec_len(normal, 1.0);

	// double plane = get_dot_product(normal_u, tr->point1);


	double t = pl_intersect(normal_u, scene->cam->pos, tr->point1, ray);
	if (t == INFINITY)
		return (INFINITY);

	// double t = (get_dot_product(normal, scene->cam->pos) + plane) / get_dot_product(normal, ray);
	// printf("t: %f\n", t);
	// if (t < 0)
		// return (INFINITY); //if plane is behind camera, return inf

	t_vec *point = gen_coord(t * ray->x, t * ray->y, t * ray->z); //account for different camera position
	t_vec *intersect = add_vectors(scene->cam->pos, point);
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
		return (t);
	}
	else
		return (-1.0);
}

int cast(t_rt_scene *scene, t_vec *ray)
{
	//iterate objects
	t_obj *tmp;
	double d;
	double d_tmp;
	int	color;

	color = 0;
	d = 1.0/0.0; 
	d_tmp = -1.0;
	tmp = scene->obj;
	if (tmp == NULL)
		return (0);
	while(tmp != NULL)
	{
		//save the closest value to the camera and return that
		if (tmp != NULL)
		{
			// ft_printf("go\n");
			if (tmp->id == sp)
			{
				d_tmp = circle(scene, tmp->type.sp, ray);
				// printf("sp %f\n", d_tmp);
				// if (d_tmp < d && d_tmp > 0.0)
				// {
				// 	d = d_tmp;
				// 	color = translate_color(tmp->color);
				// }
			//fix when sphere is on top of me
			}
			else if (tmp->id == sq)
			{
				d_tmp = square(scene, tmp->type.sq, ray);
				// printf("sq %f\n", d_tmp);
				
				// if (d_tmp < d && d_tmp > 0.0)
				// {
				// 	d = d_tmp;
				// 	color = translate_color(tmp->color);
				// }

			}
			else if (tmp->id == tr)
			{
				d_tmp = triangle(scene, tmp->type.tr, ray);
				// printf("tr %f, %x\n", d_tmp, translate_color(tmp->color));
				// if (d_tmp < d && d_tmp > 0.0)
				// {
				// 	d = d_tmp;
				// 	color = translate_color(tmp->color);
				// }
			}
			else if (tmp->id == cy)
			{
				d_tmp = cylinder(scene, tmp->type.cy, ray);
			}
			else if (tmp->id == pl)
			{
				d_tmp = plane_intersect(scene, tmp->type.pl, ray);
				// printf("pl %f\n", d_tmp);
			
			}
		}
		if (d_tmp < d && d_tmp >= 0.0)
		{
			d = d_tmp;
			color = translate_color(tmp->color);
		}
		tmp = tmp->next;
	}


	//testing
	// double t = -15 / ray->z;

	// if (t * ray->x < 5.0 && t * ray->x > -5.0 && t * ray->y + 0.5 < 0.05 && t * ray->y + 0.5 > -0.05)
		// color = 0xff0000;
	//square calculation is off
	

	// printf("distance: %f\n", d);
	// printf("\n");
	return (color);
}

int remap_coord(t_rt_scene *scene, t_vec *pos, t_cam_info cam_data, t_qua *q)
{

	//currently I'm stretching image based on fov and aspect ratio difference. Do i want to??
	// double aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y; //account for non square res
	// double fov_a_ratio = (double)scene->cam->fov / (double)FOV_VERT; //maybe bad, please double check
	// ft_printf("aspect ratio: %f\n", aspect_ratio);
	// double fov_y = tan(FOV_VERT / 2 * M_PI / 180);
	// double fov_x = tan(scene->cam->fov / 2 * M_PI / 180);
	double PixelScreenx = ((pos->x * 2) - 1) * cam_data.aspect_ratio * cam_data.len_x;
	double PixelScreeny = (1 - (pos->y * 2)) * cam_data.len_y * cam_data.fov_ratio; //changes vertical fov slightly, so i can see a bit further/less depending on horizontal fov. Makes squishing slightly better, but I might want to use a different value or pillarbox instead. Quickie solution
	// ft_printf("ray: (%f, %f, %f), pos: (%f, %f, %f) fov_a_ratio: %f\n", PixelScreenx, PixelScreeny, pos->z, pos->x, pos->y, pos->z, fov_a_ratio);
	
	t_vec *vec = gen_coord(PixelScreenx, PixelScreeny, -1);
	t_vec *ray = orient_vector(q, vec);
	// t_vec *ray = gen_coord(PixelScreenx, PixelScreeny, pos->z); //Ray's direction ray
	
	
	// ft_printf("ray: (%f, %f, %f), len: %f\n", ray->x, ray->y, ray->z, det_len_vec(ray));
	
	return (cast(scene, ray));
}


//get ndc space
void get_ndc_coords(t_rt_scene *scene, void *mlx_ptr, void *win_ptr)
{
	size_t i;
	size_t j;
	double inc_x;
	double inc_y;
	t_vec *pos;
	t_cam_info cam_data;

	cam_data.aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y;
	cam_data.fov_ratio = (double)scene->cam->fov / (double)FOV_VERT; //changing maybe
	cam_data.len_x = tan(scene->cam->fov / 2 * M_PI / 180);
	cam_data.len_y = tan(FOV_VERT / 2 * M_PI / 180);

	i = 1;
	j = 1;
	inc_x = 1.0/scene->res->res_x;
	inc_y = 1.0/scene->res->res_y;
	pos = (t_vec*)e_malloc(sizeof(t_vec));
	pos->z = -1; //we'll need to find the real number for this
	// pos->x = inc_x / 2;
	// pos->y = inc_y / 2;

	pos->x = 0;//
	pos->y = 0;//

	t_vec *base = gen_coord(0, 0, -1);
	//determnie_quaternion(to this vector, from this vector)
	t_qua *q = determine_quaternion(scene->cam->orien, base);
	
	// ft_printf("quaternion: (%f, %f, %f, %f)\n", q->w, q->vector->x, q->vector->y, q->vector->z);

	// t_vec *v_c = conjugate_vector(q, pos);

//	TESTING ------------------------------

	// t_vec *dire = gen_coord(0, 1, 1);//
	// t_qua *q_test = determine_quaternion(base, dire);//

	// t_vec *test = set_vec_len(orient_vector(q_test, dire), 1);//
	// t_vec *test = orient_vector(q_test, dire);//
	// t_vec *check = set_vec_len(base, 1);
	// ft_printf("Is this\t(%f, %f, %f)\n", test->x, test->y, test->z);
	// ft_printf("Should be this\t(%f, %f, %f)\n", check->x, check->y, check->z);

	// ft_printf("%f, %f\n", inc_x, inc_y);

//	DONE TESTING ---------------------------



	int color;

	// while (j <= 2)
	while (j <= scene->res->res_y)
	{
		// while (i <= 2)
		while (i <= scene->res->res_x)
		{
			//get coord here.
			// ft_printf("pix:\t(%d, %d)\tndc:\t(%f, %f, %f)\n", i, j, pos->x, pos->y,pos->z);
			// if (i == 250 && j == 250)
			// {
			
			// if (remap_coord(scene, pos))
			// {
				// ft_printf("true\n");
				// if (i == 250 && j == 250)

					color = 0;
					// if (j == 1 && i == 250)
					color = remap_coord(scene, pos, cam_data, q);
					// printf("%x\n", color);
					// if (color != 0)
					// printf("pixel: %ld, %ld\n", j, i);
					// if (j == 280)
						// printf("color %x, pixel: %ld, %ld\n\n", color, j, i);
						// color = 0xff0000;	
					mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
			// }
			// else
			// {
				// ft_printf("false\n");
				// mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);
			// }
			if (i != scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 1;
		pos->x = inc_x /2;
		// ft_printf("if %f < 1.0\n", pos->y + inc_y);
		if (j != scene->res->res_y)
		{
			pos->y += inc_y;
		}
		j++;

		// printf("\n\n");
	}
	// ft_printf("done\n");
}

// void get_fisheye_ndc_coords(t_rt_scene *scene)
// {
// 	//view plane coords start from (-res_x/2, res_y/2). These can be translated then to the screen.
// 	//Then translate this to coords within (-1, 1) to (1, -1). These are fisheye ndc coords
// 	double x_start;
// 	double y_start;
// 	int i;
// 	int j;

// 	x_start = (scene->res->res_x/2.0)*-1;
// 	y_start = (scene->res->res_y/2.0);
// 	i = 0;
// 	j = 0;
// 	ft_printf("%f, %f\n", x_start, y_start);
// 	while ()
// 	{
		
// 	}
// }

void	trace(t_rt_scene *scene, void *mlx_ptr, void *win_ptr)
{
	get_ndc_coords(scene, mlx_ptr, win_ptr);
	// get_fisheye_ndc_coords(scene);
}

void trace_them_rays(t_rt_scene *scene)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int y;
	int color;

	y = 100;
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT);
	//direction vector for a straight vector for collision checking.
	// t_vec *dir = determine_vector(scene->cam->pos, scene->cam->orien);
	// ft_printf("vector: (%f, %f, %f)\n", dir->x, dir->y, dir->z);


	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "miniRT");
	trace(scene, mlx_ptr, win_ptr);

	//get straight vector
	//get position of current pixel
	//apply straight vector with current pixel to check for collision

	
	

	// color = translate_color(scene->amb->color);
	// ft_printf("%x\n", color);
	// while(y < 300)
	// {
	// 	mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
	// 	color += 1;
	// 	y++;
	// }
	mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
}