// #include "color.h"
#include "rt.h"
#include "render.h"
#include "error.h"
#include <math.h>
#include <stdio.h>//

#include "libft.h"//

//TODO: remember to take into account opposite orientation (should work now)



int check_intersections(t_rt_scene *scene, t_light *light, t_vec *point)
{
	double hit_tmp;
	t_obj *tmp_obj;

	hit_tmp = -1;
	tmp_obj = scene->obj;
	if (tmp_obj == NULL)
		return (0);
	t_vec *sec = substract_vectors(light->pos, point);
	t_vec *sec_u = set_vec_len(sec, 1);
	double sec_len = det_len_vec(sec); //sec is vector from point to light
    t_vec *eps = set_vec_len(sec, EPSILON); //to not intersect self
    t_vec *point_new = add_vectors(point, eps); //to not intersect self
	while (tmp_obj != NULL)
	{
		hit_tmp = check_obj_intersect(tmp_obj, sec_u, point_new, hit_tmp);
		if ((hit_tmp > 0 && hit_tmp < sec_len) || hit_tmp == INSIDE_OBJ)
			return (1);
		tmp_obj = tmp_obj->next;
	}
	return (0);
}

t_color *calculate_shading(t_rt_scene *scene, t_obj *obj, t_camera *cam, t_vec *point, t_color *amb_base)
{
	t_light *tmp;
	t_vec *R;
	t_vec *R_u;
	t_color *final_color;
	t_vec *normal;
	double dot;
	int i;

	tmp = scene->light;
	i = 0;
	int tmp_red = 0;
	int tmp_green = 0;
	int tmp_blue = 0;
	if (tmp == NULL) //change this shit
		return (amb_base);
	final_color = (t_color *)e_malloc(sizeof(t_color));
	normal = calculate_normal(obj, point, cam); //if normal is to the opposite direction, from light, r
	while (tmp != NULL)
	{
		if (tmp != NULL)
		{
			R = substract_vectors(tmp->pos, point); //ray from hit point to light
			R_u = set_vec_len(R, 1); //ray from hit point to light
			if (check_intersections(scene, tmp, point))
			{
				i++;
			}
			else
			{
				dot = get_dot_product(normal, R_u);
				if (dot < 0)
					dot = 0;
				tmp_red += tmp->brightness * tmp->color->r * dot; //instead of one use 0.18 or equivalent
				tmp_green += tmp->brightness * tmp->color->g * dot;
				tmp_blue += tmp->brightness * tmp->color->b * dot;
				i++;
			}
			tmp = tmp->next;
		}
	}
	if (i == 0)
		return (amb_base);
	int light_r = (tmp_red + amb_base->r) / (i + 1);
	int light_g = (tmp_green + amb_base->g) / (i + 1);
	int light_b = (tmp_blue + amb_base->b) / (i + 1);

		final_color->r = sqrt((light_r * obj->color->r));
		final_color->g = sqrt((light_g * obj->color->g));
		final_color->b = sqrt((light_b * obj->color->b));

	return (final_color);
}

t_color *calculate_final_color(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_camera *cam)
{
	t_color *amb_base;
	t_color *final_color;
	t_vec *point;

	amb_base = (t_color *)e_malloc(sizeof(t_color));
	amb_base->r = sqrt(color->r * scene->amb->color->r) * scene->amb->ratio;
	amb_base->g = sqrt(color->g * scene->amb->color->g) * scene->amb->ratio;
	amb_base->b = sqrt(color->b * scene->amb->color->b) * scene->amb->ratio;
	amb_base = 
	point = find_point(cam->pos, ray, d); //pass this to check_intersections
	final_color = calculate_shading(scene, obj, cam, point, amb_base);
	free(point);
	free(amb_base);
	return (final_color);
}