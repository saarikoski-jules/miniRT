// #include "color.h"
#include "rt.h"
#include "render.h"
#include "error.h"
#include <math.h>
#include <stdio.h>//

#include "libft.h"//

//TODO: remember to take into account opposite orientation (should work now)

t_vec *apply_epsilon(t_vec *point, t_vec *ray)
{
	t_vec *new;
	t_vec *eps;

    eps = set_vec_len(ray, EPSILON); //to not intersect self
    new = add_vectors(point, eps); //to not intersect self
	free(eps);
	return (new);
}

t_vec	*find_len_and_get_u(double *len, t_vec *from, t_vec *to)
{
	t_vec *vec;
	t_vec *vec_u;
	
	vec = substract_vectors(from, to);//actually other way around?
	*len = det_len_vec(vec); //sec is vector from point to light
	vec_u = set_vec_len(vec, 1);
	free(vec);
	return (vec_u);
}

t_color_int *init_color_int(int r, int g, int b)
{
	t_color_int *color;

	color = (t_color_int *)e_malloc(sizeof(t_color_int));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

void	add_color_and_free(t_color_int **color_prev, t_color_int **color_new)
{
	(*color_prev)->r += (*color_new)->r;
	(*color_prev)->g += (*color_new)->g;
	(*color_prev)->b += (*color_new)->b;
	free(*color_new);
	*color_new = NULL;
}

int	check_intersections(t_rt_scene *scene, t_light *light, t_vec *point)
{
	double	hit_tmp;
	t_obj	*tmp_obj;
	t_vec	*sec_u;
	double	sec_len;
	t_vec	*point_new;

	hit_tmp = NO_INTERSECT;
	tmp_obj = scene->obj;
	if (tmp_obj == NULL)
		return (0);
	sec_u = find_len_and_get_u(&sec_len, light->pos, point);
	point_new = apply_epsilon(point, sec_u);
	while (tmp_obj != NULL)
	{
		hit_tmp = check_obj_intersect(tmp_obj, sec_u, point_new, hit_tmp);
		if ((hit_tmp > 0 && hit_tmp < sec_len) || hit_tmp == INSIDE_OBJ)
		{
			return (1);
		}
		tmp_obj = tmp_obj->next;
	}
	free(sec_u);
	free(point_new);
	return (0);
}

t_color_int **build_color(t_vec *point, t_vec *normal, t_rt_scene *scene, t_light *light)
{
	t_vec		*R;
	t_vec		*R_u;
	double		dot;
	t_color_int *new_color;
	t_color_int **col;

	R = substract_vectors(light->pos, point); //ray from hit point to light
	R_u = set_vec_len(R, 1); //ray from hit point to light
	new_color = init_color_int(0, 0, 0);
	if (check_intersections(scene, light, point) == 0)
	{
		dot = get_dot_product(normal, R_u);
		if (dot < 0)
			dot = 0;
		new_color->r += light->brightness * light->color->r * dot; //instead of one use 0.18 or equivalent
		new_color->g += light->brightness * light->color->g * dot;
		new_color->b += light->brightness * light->color->b * dot;
	}
	free(R);
	free(R_u);
	col = &new_color;
	return (col);
}

t_color *calculate_shading(t_rt_scene *scene, t_vec *normal, t_vec *point)
{
	t_light *tmp;
	t_color *amb_base;
	t_color *light;
	int i;
	t_color_int *color_tmp;

	color_tmp = init_color_int(0, 0, 0);
	amb_base = gen_color(scene->amb->color->r * scene->amb->ratio,
						scene->amb->color->g * scene->amb->ratio,
						scene->amb->color->b * scene->amb->ratio);
	tmp = scene->light;
	i = 0;
	while (tmp != NULL)
	{
		add_color_and_free(&color_tmp,
			build_color(point, normal, scene, tmp));
		i++;
		tmp = tmp->next;
	}
	light =	gen_color((color_tmp->r + amb_base->r) / (i + 1),
						(color_tmp->g + amb_base->g) / (i + 1),
						(color_tmp->b + amb_base->b) / (i + 1));
	free(amb_base);
	free(color_tmp);
	return (light);
}

t_color *calculate_final_color(t_rt_scene *scene, t_vec **point, t_obj *obj, t_camera *cam)
{
	t_color	*final_color;
	t_color	*light;
	t_vec	*normal;

	normal = calculate_normal(obj, *point, cam); //if normal is to the opposite direction, from light, r
	light = calculate_shading(scene, normal, *point);
	final_color = (t_color *)e_malloc(sizeof(t_color));
	final_color->r = sqrt((light->r * obj->color->r));
	final_color->g = sqrt((light->g * obj->color->g));
	final_color->b = sqrt((light->b * obj->color->b));
	free(normal);
	free(*point);
	*point = NULL;
	free(light);
	return (final_color);
}