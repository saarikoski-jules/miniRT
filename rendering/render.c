#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "quaternion.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//
#include <parse.h>

#define DIST 1 //choose: determine camera distance from grid
#define FOV_VERT 60 //choose: determine vertical fov
//choose: default rotation of camera, should be changeable.


// 	// ☺

//TODO: if two items are on the exact same 2D plane, which one displays? Right now the one mentioned earlier in the .rt file is displayed
//TODO: square is not visible if your camera and square orientation are the same
//TODO: cylinders break when seen more from the direction of the endcaps
//TODO: cylinder is rendered slightly wider than it's meant to
//TODO: what happens when any object is on top of me


double circle(t_rt_scene *scene, t_sp *sp, t_vec *ray, t_vec **n)
{
	//sphere seems to be a bit too low compared to the square in some cases

	t_vec *ray_u = set_vec_len(ray, 1);

	t_vec *L = substract_vectors(scene->cam->pos, sp->pos);
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
	t_vec *i_point = add_vectors(intersect, scene->cam->pos);
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

double plane_intersect(t_rt_scene *scene, t_pl *pl, t_vec *ray, t_vec **n)
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
	*n = set_vec_len(pl->orien, 1);
	return (t); //t should be the actual distance as it's calculated with a unit vector
}

double square(t_rt_scene *scene, t_sq *sq, t_vec *ray, t_vec **n)
{
	t_vec *orien_u;
	double t;

	t_vec *BA = substract_vectors(sq->point2, sq->point1);
	t_vec *CA = substract_vectors(sq->point3, sq->point1);
	t_vec *normal = get_cross_product(BA, CA);
	orien_u = set_vec_len(normal, 1.0);
	// orien_u = set_vec_len(sq->orien, 1); // breaks when the same with camera orientation
	//t may not be distance, is this calculated with unit vector
	t = pl_intersect(sq->orien, scene->cam->pos, sq->point1, ray);
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
	//cylinder distance calculation is off. Cylinder shaft seems to be a little bit too far away
	//start pos of ray, cy, n (normal)

	t_vec *O;
	t_vec *OC = substract_vectors(ray_start, cy->pos); //start_pos, cy->pos
	double OC_len = det_len_vec(OC);
	t_vec *OC_u = set_vec_len(OC, 1);
	t_vec *turn = orient_vector(cy->q, OC_u);
	t_vec *cam_dist = set_vec_len(turn, OC_len);
	O = add_vectors(cam_dist, cy->pos); 

	t_vec *p = substract_vectors(O, cy->pos);

	// t_vec *p = cy->pos;

	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *R = orient_vector(cy->q, ray_u);

	t_vec *O_2d = gen_coord(O->x, O->y, 0);
	t_vec *R_2d = gen_coord(R->x, R->y, 0);
	
	
	// if (det_len_vec(R) != 1.0)
	// {
		// printf("vector length: %.15f\n", det_len_vec(R));
	// }
	
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
	//This isn't working

	// t_vec *pos = gen_coord(intersection->z * cy->orien->x, intersection->z * cy->orien->y, intersection->z * cy->orien->z);
	// t_vec *pos_c = add_vectors(cy->pos, pos);
	
	//Get position along the orien of the cylinder
	t_vec *pos_offset = set_vec_len(cy->orien, intersection->z); //works if this is unit vecs
	// t_vec *pos = 
	// t_vec *pos = add_vectors(cy->pos, pos_offset);
	t_vec *pos_c = substract_vectors(cy->pos, pos_offset);
	// t_vec *pos_c = add_vectors(ray_start, pos); //breaks somehow..?

	t_vec *i_real = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z);
	t_vec *i_real_c = add_vectors(i_real, ray_start);
	t_vec *normal = substract_vectors(i_real_c, pos_c);
	printf("position on axis: (%f, %f, %f)\n", pos_c->x, pos_c->y, pos_c->z);
	printf("intersection point: (%f, %f, %f)\n\n", i_real_c->x, i_real_c->y, i_real_c->z);
	*n = set_vec_len(normal, 1);//PROBLEM BE HERE BIRCHES
	// printf("pos_c: (%f, %f, %f) i_real_c: (%f, %f, %f)\n", pos_c->x, pos_c->y, pos_c->z, i_real_c->x, i_real_c->y, i_real_c->z);
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

double triangle(t_rt_scene *scene, t_tr *tr, t_vec *ray, t_vec **n)
{
	//calculate normal
	//is the positioning of my triangles strange?
	t_vec *BA = substract_vectors(tr->point2, tr->point1);
	t_vec *CA = substract_vectors(tr->point3, tr->point1);
	t_vec *normal = get_cross_product(BA, CA);
	t_vec *normal_u = set_vec_len(normal, 1.0);

	double t = pl_intersect(normal_u, scene->cam->pos, tr->point1, ray);
	if (t == INFINITY)
		return (INFINITY);

	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *point = gen_coord(t * ray_u->x, t * ray_u->y, t * ray_u->z); //account for different camera position
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
		*n = normal_u;
		return (t); //t is always 10. It should not be? Calculate distance to current intersection point
	}
	else
		return (-1.0);
}

int check_intersections(t_rt_scene *scene, t_vec *ray, double d, t_light *light)
{
	//get point on object surface = cam->pos + d * ray
	// double epsilon = 0.000001; //to prevent objects intersecting with themselves
	double epsilon = -0.000001; //to prevent objects intersecting with themselves
	t_vec *intersection = gen_coord(d * ray->x - epsilon, d * ray->y - epsilon, d * ray->z - epsilon); //wont work for everything, make sure to move intersection point a little towards the light
	t_vec *point = add_vectors(scene->cam->pos, intersection);

	//check if there is an intersection on the vector between light and all objects


	double hit = -1;
	double hit_tmp = -1;
	t_obj *tmp_obj;
	tmp_obj = scene->obj;
	if (tmp_obj == NULL)
		return (0);

		// printf("hit pos: (%f, %f, %f)\n", point->x, point->y, point->z);
		// printf("check intersections\n");
		// printf("light pos (%f, %f, %f)\n\n", light->pos->x, light->pos->y, light->pos->z);
	t_vec *norm = gen_coord(0, 0, 0);
	t_vec *sec = substract_vectors(point, light->pos);
	t_vec *sec_u = set_vec_len(sec, 1);
	double sec_len = det_len_vec(sec); //sec is vector from point to light
	while(tmp_obj != NULL)
	{
		// printf("whoah this is so slow..\n");
		if (tmp_obj != NULL)
		{
			if (tmp_obj->id == sp)
			{
				hit_tmp = circle(scene, tmp_obj->type.sp, sec, &norm);
				//fix when sphere is on top of me
			}
			else if (tmp_obj->id == sq)
			{
				hit_tmp = square(scene, tmp_obj->type.sq, sec, &norm);
			}
			else if (tmp_obj->id == tr)
			{
				hit_tmp = triangle(scene, tmp_obj->type.tr, sec, &norm);
			}
			else if (tmp_obj->id == cy)
			{
				// t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n
				hit_tmp = cylinder(scene, point, sec_u, tmp_obj->type.cy, &norm);

			}
			else if (tmp_obj->id == pl)
			{
				hit_tmp = plane_intersect(scene, tmp_obj->type.pl, sec, &norm);
			}
		}
		// if (hit_tmp > 0 && hit_tmp < 1) //is less than distance to light

		//Intersects itself
		if (hit_tmp > 0 && hit_tmp < sec_len)
		{
			// printf("\n\nINTERSECTION hit_tmp: %f, sec len: %f\n\n", hit_tmp, sec_len);
			// return (hit_tmp);
			// return (1);
			return (0);
		}
		tmp_obj = tmp_obj->next;

	}

	//hit should be between 0 and 1 for there to be an intersection between point and light
	// if ()
	// printf("hit: %f\n", hit);
		return (0);
	//return 0 if there are no intersections
}

// t_vec *calculate_normal(t_vec *ray, t_vec *hit, t_obj *obj)
// {

// }


t_color *calculate_shading(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n)
{

	// printf("lights\n");
	t_light *tmp;
	int i;

	tmp = scene->light;
	i = 1;
	int tmp_red = color->r;
	int tmp_green = color->g;
	int tmp_blue = color->b;
	if (tmp == NULL)
		return (color);
	//calculate intersection here
	// t_vec *N = calculate_normal(ray, intersection, obj); //normal to the hit point
	t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *intersect = gen_coord(d * ray_u->x, d * ray_u->y, d * ray_u->z);
	t_vec *point = add_vectors(intersect, scene->cam->pos);
	t_vec *R;
	t_vec *R_u;
	double dot;

	while(tmp != NULL)
	{
		if (tmp != NULL)
		{
			R = substract_vectors(tmp->pos, point); //ray from hit point to light
			R_u = set_vec_len(R, 1); //ray from hit point to light
			
			// printf("light: (%d, %d, %d)\n", tmp->color->r, tmp->color->g, tmp->color->b);

			//if light hits object, i++
			if (check_intersections(scene, ray, d, tmp))
			{
				printf("Calculate shadow\n");
			}
			else
			{
				//Calculate bright spot
				dot = get_dot_product(n, R_u);
				// printf("Ray: (%f, %f, %f)\nnormal: (%f, %f, %f)\n", R->x, R->y, R->z, n->x, n->y, n->z);
				// printf("dot: %f\n", dot);
				// printf("past check intersections\n\n");
				//Do this for the color generated by light and its distance
				double brightness_ratio = 1; //how close the light is??
				if (dot < 0)
					dot = 0;

				tmp_red += brightness_ratio * tmp->brightness * tmp->color->r * dot; //instead of one use 0.18 or equivalent
				tmp_green += brightness_ratio * tmp->brightness * tmp->color->g * dot;
				tmp_blue += brightness_ratio * tmp->brightness * tmp->color->b * dot;
				// tmp_green += tmp->color->g;
				// tmp_blue += tmp->color->b;
				i++;
			}
			tmp = tmp->next;
		}
	}
	t_color *final_color = (t_color*)e_malloc(sizeof(t_color));
	// if (i != 0)
	// {
		//instead of this do a shadow darker/brighter calculation
		// final_color->r = tmp_red / i;
		// final_color->g = tmp_green / i;
		// final_color->b = tmp_blue / i;
	// }
	// else
	// {
		final_color->r = tmp_red / 2;
		final_color->g = tmp_green / 2;
		final_color->b = tmp_blue / 2; //this won't work for getting the correct color
	
	// printf("tmp: (%d, %d, %d)\ncolor (%d, %d, %d)\n", tmp_red, tmp_green, tmp_blue, color->r, color->g, color->b);
	// printf("final: (%d, %d, %d)\n", final_color->r, final_color->g, final_color->b);
	// }
	// printf("number of lights: %d\n", i);
	// printf("\n");
	// return (final_color);
	return (final_color);
}

t_color *calculate_final_color(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n)
{
	// printf("color: (%d, %d, %d)\n", color->r, color->g, color->b);
	// printf("Ambiance: ratio: %f, color: (%d, %d, %d)\n", scene->amb->ratio, scene->amb->color->r, scene->amb->color->g, scene->amb->color->b);
	// scene->amb->ratio
	// to get base color, calculate the ambient light and object color ratio
	t_color *amb_base = (t_color *)e_malloc(sizeof(t_color));
	//calculate color ratio:
	// int r = scene->amb->color->r * scene->amb->ratio;
	amb_base->r = sqrt(color->r * scene->amb->color->r) * scene->amb->ratio;
	// printf("final red: %d\n", amb_base->r);
	// int g = scene->amb->color->g * scene->amb->ratio;
	amb_base->g = sqrt(color->g * scene->amb->color->g) * scene->amb->ratio;
	// printf("final green: %d\n", amb_base->g);
	// int b = scene->amb->color->b * scene->amb->ratio;
	amb_base->b = sqrt(color->b * scene->amb->color->b) * scene->amb->ratio;
	// printf("final blue: %d\n", amb_base->b);

	//make sure to validate color
	
	//rotate through all the lights and calculate lights and shadows

	// printf("final color: (%d, %d, %d)\n", final_color->r, final_color->g, final_color->b);
	// printf("color: (%d, %d, %d)\n\n", amb_base->r, amb_base->g, amb_base->b);
	// return (final_color);
	//This should never happen

	if (n->x == 0 && n->y == 0 && n->z == 0)
		printf("0,0,0\n");
	t_color *final_color = calculate_shading(scene, ray, amb_base, d, obj, n);
	// return (final_color); //make sure to validate color
	return (final_color);
}

int cast(t_rt_scene *scene, t_vec *ray)
{
	t_obj *tmp;
	double d;
	double d_tmp;
	int	color;
	color = 0;
	d = 1.0/0.0; 
	d_tmp = -1.0;
	tmp = scene->obj;
	t_vec *n;
	n = gen_coord(0, 0, 0);
	if (tmp == NULL)
		return (0);
	while(tmp != NULL)
	{
		if (tmp != NULL)
		{
			if (tmp->id == sp)
			{
				d_tmp = circle(scene, tmp->type.sp, ray, &n);
				//fix when sphere is on top of me
				// printf("sp\n");
			}
			else if (tmp->id == sq)
			{
				d_tmp = square(scene, tmp->type.sq, ray, &n);
				// printf("sq\n");
			}
			else if (tmp->id == tr)
			{
				d_tmp = triangle(scene, tmp->type.tr, ray, &n);
				// printf("tr\n");
			}
			else if (tmp->id == cy)
			{
				// t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n
				d_tmp = cylinder(scene, scene->cam->pos, ray, tmp->type.cy, &n);
				printf("cy\n");
			}
			else if (tmp->id == pl)
			{
				d_tmp = plane_intersect(scene, tmp->type.pl, ray, &n);
				printf("pl\n");
			}
		}

		if (d_tmp < d && d_tmp >= 0.0)
		{
			d = d_tmp;
			//get position from d, ray and camera position. Trace vector from point to all cameras and calculate combined color including ambiance
			t_color *rgb = calculate_final_color(scene, ray, tmp->color, d, tmp, n);  //fix this so it's only ran once per pixel??
			color = translate_color(rgb);
			// printf("dist: %f\n", d);
			// t_color *rgb = tmp->color;
		}
		tmp = tmp->next;
	}
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
	pos->x = inc_x / 2;
	pos->y = inc_y / 2;

	// pos->x = 0;//
	// pos->y = 0;//

	t_vec *base = gen_coord(0, 0, -1);
	t_qua *q = determine_quaternion(scene->cam->orien, base);
	int color;

	// while (j <= 2)
	while (j <= scene->res->res_y)
	{
		// while (i <= 2)
		while (i <= scene->res->res_x)
		{
			color = remap_coord(scene, pos, cam_data, q);
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, color); //create image and put all at once instead.

			if (i != scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 1;
		pos->x = inc_x /2;
		if (j != scene->res->res_y)
		{
			pos->y += inc_y;
		}
		j++;
	}
	printf("done\n");
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