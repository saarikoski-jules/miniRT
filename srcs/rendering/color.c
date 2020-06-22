/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 11:49:21 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:10:25 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "error.h"
#include <math.h>

int			check_intersections(t_rt_scene *scene, t_light *light, t_vec *point)
{
	double	hit_tmp;
	t_obj	*tmp_obj;
	t_vec	*sec_u;
	double	sec_len;
	t_vec	*point_new;

	hit_tmp = NO_INTERSECT;
	tmp_obj = scene->obj;
	sec_u = find_len_and_get_u(&sec_len, light->pos, point);
	point_new = apply_epsilon(point, sec_u);
	while (tmp_obj != NULL)
	{
		hit_tmp = check_obj_intersect(tmp_obj, sec_u, point_new, hit_tmp);
		if ((hit_tmp > 0 && hit_tmp < sec_len) || hit_tmp == INSIDE_OBJ)
		{
			free(sec_u);
			free(point_new);
			return (1);
		}
		tmp_obj = tmp_obj->next;
	}
	free(sec_u);
	free(point_new);
	return (0);
}

t_color_int	**build_color(t_vec *point, t_vec *normal,
							t_rt_scene *scene, t_light *light)
{
	t_vec		*r;
	t_vec		*r_u;
	double		dot;
	t_color_int *new_color;
	t_color_int **col;

	r = substract_vectors(light->pos, point);
	r_u = set_vec_len(r, 1);
	new_color = init_color_int(0, 0, 0);
	if (check_intersections(scene, light, point) == 0)
	{
		dot = get_dot_product(normal, r_u);
		if (dot < 0)
			dot = 0;
		new_color->r += light->brightness * light->color->r * dot;
		new_color->g += light->brightness * light->color->g * dot;
		new_color->b += light->brightness * light->color->b * dot;
	}
	free(r);
	free(r_u);
	col = &new_color;
	return (col);
}

t_color		*calculate_shading(t_rt_scene *scene, t_vec *normal, t_vec *point)
{
	t_color_int	*color_tmp;
	t_light		*tmp;
	t_color		*amb_base;
	t_color		*light;
	int			i;

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
	light = gen_color((color_tmp->r + amb_base->r) / (i + 1),
						(color_tmp->g + amb_base->g) / (i + 1),
						(color_tmp->b + amb_base->b) / (i + 1));
	free(amb_base);
	free(color_tmp);
	return (light);
}

t_color		*calculate_final_color(t_rt_scene *scene, t_vec **point,
								t_obj *obj, t_camera *cam)
{
	t_color	*final_color;
	t_color	*light;
	t_vec	*normal;

	normal = calculate_normal(obj, *point, cam);
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
