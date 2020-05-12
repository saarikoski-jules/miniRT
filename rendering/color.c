// #include "color.h"
#include "rt.h"
#include "render.h"
#include "error.h"
#include <math.h>
#include <stdio.h>//

//TODO: remember to take into account opposite orientation

int check_intersections(t_rt_scene *scene, t_vec *ray, double d, t_light *light)
{
	//get point on object surface = cam->pos + d * ray
	// double epsilon = 0.000001; //to prevent objects intersecting with themselves
	// double epsilon = -0.000001; //to prevent objects intersecting with themselves
	// t_vec *intersection = gen_coord(d * ray->x - epsilon, d * ray->y - epsilon, d * ray->z - epsilon); //wont work for everything, make sure to move intersection point a little towards the light
    t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *intersection = gen_coord(d * ray_u->x, d * ray_u->y, d * ray_u->z); //wont work for everything, make sure to move intersection point a little towards the light
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
	t_vec *sec = substract_vectors(light->pos, point);
	t_vec *sec_u = set_vec_len(sec, 1);
	double sec_len = det_len_vec(sec); //sec is vector from point to light
    t_vec *epsilon = set_vec_len(sec, 0.00000001); //to not intersect self
    t_vec *point_new = add_vectors(point, epsilon); //to not intersect self
    //INSTEAD OF MOVING POINT TOWARD LIGHT, SHOULD MOVE POINT TOWARD SELF
    // t_vec *IC = add_vectors(point, scene->cam->pos);
    // t_vec *epsilon = set_vec_len(IC, 0.000000001);
    // t_vec *point_new = add_vectors(point, epsilon);
    // point_new = point;


	while(tmp_obj != NULL)
	{
		// printf("whoah this is so slow..\n");
		if (tmp_obj != NULL)
		{
			if (tmp_obj->id == sp)
			{
				// hit_tmp = circle(scene, point, tmp_obj->type.sp, sec, &norm);
                // printf("hit: %f\n", hit_tmp );
				//fix when sphere is on top of me
				// hit_tmp = circle(scene, point, sec_u, tmp_obj->type.sp, &norm);
				hit_tmp = sp_intersect(point_new, sec_u, tmp_obj->type.sp); //to not intersect self
				// if (hit_tmp >= 0 && hit_tmp != INFINITY)
					// printf("hit_tmp cp: %f\n", hit_tmp);
            }
			else if (tmp_obj->id == sq)
			{
				// hit_tmp = square(scene, point, tmp_obj->type.sq, sec, &norm);
				// hit_tmp = square(scene, point, sec_u, tmp_obj->type.sq, &norm);
				hit_tmp = sq_intersect(point_new, sec_u, tmp_obj->type.sq);
			
            }
			else if (tmp_obj->id == tr)
			{
				// hit_tmp = triangle(scene, point, tmp_obj->type.tr, sec, &norm);
				// hit_tmp = triangle(scene, point, sec_u, tmp_obj->type.tr, &norm);
				hit_tmp = tr_intersect(point_new, sec_u, tmp_obj->type.tr);
			
            }
			else if (tmp_obj->id == cy)
			{
				// t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n
				// hit_tmp = cylinder(scene, point, sec_u, tmp_obj->type.cy, &norm);
				hit_tmp = cy_intersect(point_new, sec_u, tmp_obj->type.cy);
                // t_vec *point_cy = substract_vectors(tmp_obj->type.cy->pos, point);
                // t_vec *point_new_cy = substract_vectors(tmp_obj->type.cy->pos, point_new);
                // if (det_len_vec(point_cy) > det_len_vec(point_new_cy))
                // {
                    // printf("Not inside obj:\nintersection: %.10f\nto direction of light: %.10f\n", det_len_vec(point_cy), det_len_vec(point_new_cy));
                    // return (1);
                // }

			}
			else if (tmp_obj->id == pl)
			{
				// hit_tmp = plane_intersect(scene, point, sec_u, tmp_obj->type.pl, &norm);

				//orien of item
				//ray start pos
				//item position
				//ray direction

				hit_tmp = pl_intersect(tmp_obj->type.pl->orien, point_new, tmp_obj->type.pl->pos, sec_u);
				// hit_tmp = pl_intersect(tmp_obj->type.pl->orien, t_vec *orien, t_vec *ray_start, t_vec *pos, t_vec *ray)

				// hit_tmp = plane_intersect(scene, point_new, sec_u, tmp_obj->type.pl, &norm); //to not intersect self

        	}
            if (hit_tmp == -10)
            {
                // printf("false:\nintersection point:\t(%.10f, %.10f, %.10f)\n\n", point->x, point->y, point->z);
                return (1);
            }
        }
		// if (hit_tmp > 0 && hit_tmp < 1) //is less than distance to light

		//Intersects itself
		// if (hit_tmp > 0 && hit_tmp < 1)
		if (hit_tmp > 0 && hit_tmp < sec_len)
		{
			// printf("here?\n");
            // printf("true:\nintersection point:\t(%.10f, %.10f, %.10f)\n\n", point->x, point->y, point->z);

            // printf("hit obj: %d\n", tmp_obj->id); //ALWAYS INTERSECTS ITSELF. Move intersect point towards light by very little
			// printf("\n\nINTERSECTION hit_tmp: %f, sec len: %f\n\n", hit_tmp, sec_len);
			// return (hit_tmp);
			return (1);
			// return (0);
		}
		tmp_obj = tmp_obj->next;

	}

	//hit should be between 0 and 1 for there to be an intersection between point and light
	// if ()
	// printf("hit: %f\n", hit);
		return (0);
	//return 0 if there are no intersections
}

t_vec *cy_normal(t_cy *cy, t_vec *intersect)
{
	t_vec *normal;

	//INSTEAD DETERMINE FROM END TO UP. THIS WILL WORK

	// normal == NULL;
	//side1 get distance from centre to intersect
	//side2 == r
	//solve side 3 of straight triangle

	//tan(angle) = opposite / adjacent

	double min_angle = cy->r / cy->h;

	// t_vec *hyp = sqrt(pow(cy->r, 2) - pow(cy->h, 2))


	t_vec *v_len = substract_vectors(intersect, cy->end1);
	double len = det_len_vec(v_len);
	double len_z;

	// printf("len: %f\n", pow(len, 2));
	// printf("r: %f\n", cy->r);

	t_vec *v_up = substract_vectors(intersect, cy->end2);
	if (det_len_vec(v_up) <= cy->r)
	{
		return (cy->orien);
	}
	else if (len <= cy->r)
	{
		return (substract_vectors(gen_coord(0,0,0),cy->orien));
	}
	else
	{
		double tot = pow(len, 2) - pow(cy->r, 2);
		// printf("tot: %f\n", tot);
		len_z = sqrt(tot); //this seems right
	// printf("new z: %.15f\n\n", len_z);

	}
	// printf("len_z: %f\n\n", len_z);
	t_vec *z = set_vec_len(cy->orien, len_z);
	t_vec *tmp = add_vectors(cy->end1, z);
	// printf("new: (%.15f, %.15f, %.15f)\n\n", tmp->x, tmp->y, tmp->z);
	// t_vec *real_inter = add_vectors(intersect, scene->cam->pos);
	normal = substract_vectors(intersect, tmp);
	

	// printf("new: (%f, %f, %f)\n\n", intersect->x, intersect->y, intersect->z);

	// t_vec *maybe_inter = add_vectors(z, normal);
	// if (maybe_inter->x == intersect->x && maybe_inter->y == intersect->y && maybe_inter->z == intersect->z)
	// {
		return (normal);
	// }
	// printf("wrong\n");
	// printf("maybe:\t\t(%.15f, %.15f, %.15f)\nintersect:\t(%.15f, %.15f, %.15f)\n\n", maybe_inter->x, maybe_inter->y, maybe_inter->z, intersect->x, intersect->y, intersect->z);
// 
	// return (NULL);

}

t_vec *calculate_normal(t_obj *obj, t_vec *intersect)
{
	t_vec *normal;
	normal = NULL;


	//for planes make sure normal is either correct or opposite orientation depending on where light comes
	if (obj->id == cy)
	{
		normal = cy_normal(obj->type.cy, intersect);
	}
	else if (obj->id == sp)
	{
		normal = substract_vectors(intersect, obj->type.sp->pos);
	}
	else if (obj->id == pl)
	{
		normal = obj->type.pl->orien;
	}
	else if (obj->id == tr)
	{
		normal = obj->type.tr->orien;
	}
	else if (obj->id == sq)
	{
		normal = obj->type.sq->orien;
	}
	else if (normal != NULL)
	{
		t_vec *normal_u = set_vec_len(normal, 1);
		return (normal_u);
	}
}

t_color *calculate_shading(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n)
{

	// printf("lights\n");
	t_light *tmp;
	int i;

	double albedo = 1; //reflection factor??
	tmp = scene->light;
	i = 0;
	int tmp_red = 0;
	int tmp_green = 0;
	int tmp_blue = 0;
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

	t_vec *normal = calculate_normal(obj, point);
	// if (normal != NULL)
	// {	
		// if ((normal->x != n->x || normal->y != n->y || normal->z != n->z) && obj->id != sp)
			// printf("n:\t(%.15f, %.15f, %.15f)\nnormal:\t(%.15f, %.15f, %.15f)\n\n", n->x, n->y, n->z, normal->x, normal->y, normal->z);
	// }
	// printf("new: (%f, %f, %f)\n", intersect->x, intersect->y, intersect->z);
	t_color *final_color = (t_color*)e_malloc(sizeof(t_color));
	//Get combined color effect on the pixel from all the lights
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
				// printf("Calculate shadow\n");
                // final_color->r = 255;
                // final_color->g = 0;
                // final_color->b = 0;
				// printf("do nothing?");
                // return (color);
				// printf("inters")
				i++;
			}
			else
			{
				//Calculate bright spot
				dot = get_dot_product(normal, R_u);
				//Do this for the color generated by light and its distance
				if (dot < 0)
					dot = 0;

				//calculate light power
				//calculate light reflected
				//light color
				//element color



				tmp_red += tmp->brightness * tmp->color->r * dot; //instead of one use 0.18 or equivalent
				tmp_green += tmp->brightness * tmp->color->g * dot;
				tmp_blue += tmp->brightness * tmp->color->b * dot;
				// tmp_green += tmp->color->g;
				// tmp_blue += tmp->color->b;
				i++;
			}
			tmp = tmp->next;
		}
	}
	
	//tmp color is combined light color * power

	if (i == 0)
		return (color);
	// if (i != 0)
	// {
		//instead of this do a shadow darker/brighter calculation
		// final_color->r = tmp_red / i;
		// final_color->g = tmp_green / i;
		// final_color->b = tmp_blue / i;
	// }
	// else
	// {
	int light_r = tmp_red / i;
	int light_g = tmp_green / i;
	int light_b = tmp_blue / i;
		// final_color->g = tmp_green / i;
		// final_color->b = tmp_blue / i; //this won't work for getting the correct color
	
	// double ratio = 1; //

		// final_color->r = ((light_r + obj->color->r) * albedo) / 2;
		// final_color->g = ((light_g + obj->color->g) * albedo) / 2;
		// final_color->b = ((light_b + obj->color->b) * albedo) / 2;


		final_color->r = sqrt((light_r * obj->color->r) * albedo);
		final_color->g = sqrt((light_g * obj->color->g) * albedo);
		final_color->b = sqrt((light_b * obj->color->b) * albedo);

	// printf("tmp: (%d, %d, %d)\ncolor (%d, %d, %d)\n", tmp_red, tmp_green, tmp_blue, color->r, color->g, color->b);
	// printf("final: (%d, %d, %d)\n", final_color->r, final_color->g, final_color->b);
	// }
	// printf("number of lights: %d\n", i);
	// printf("\n");
	// return (final_color);

	//Add the color effect to actual color
	

	//total color should be element_color * light_color * light_brigtness * reflection



	return (final_color);
}

t_color *calculate_final_color(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n)
{
	// printf("color: (%d, %d, %d)\n", color->r, color->g, color->b);
	// printf("Ambiance: ratio: %f, color: (%d, %d, %d)\n", scene->amb->ratio, scene->amb->color->r, scene->amb->color->g, scene->amb->color->b);
	// scene->amb->ratio
	// to get base color, calculate the ambient light and object color ratio
	t_color *amb_base = (t_color *)e_malloc(sizeof(t_color));
	t_color *final_color = (t_color *)e_malloc(sizeof(t_color));
	t_color *light_base = (t_color *)e_malloc(sizeof(t_color));
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

	// if (n->x == 0 && n->y == 0 && n->z == 0)
		// printf("0,0,0\n");
	


	light_base = calculate_shading(scene, ray, amb_base, d, obj, n);

	final_color->r = (light_base->r + amb_base->r) / 2;
	final_color->g = (light_base->g + amb_base->g) / 2;
	final_color->b = (light_base->b + amb_base->b) / 2;

	// amb_base->b = sqrt(color->b * scene->amb->color->b) * scene->amb->ratio;

	// final_color->r = sqrt(amb_base->r * scene->amb->color->r) * scene->amb->ratio;
	// final_color->g = sqrt(amb_base->g * scene->amb->color->g) * scene->amb->ratio;
	// final_color->b = sqrt(amb_base->b * scene->amb->color->b) * scene->amb->ratio;

	// return (final_color); //make sure to validate color
	return (final_color);
}