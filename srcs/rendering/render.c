/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 17:50:33 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 17:51:39 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "collision_utils.h"
#include <math.h>

double	check_obj_intersect(t_obj *obj_tmp, t_vec *ray, t_vec *pos,
							double d_tmp)
{
	if (obj_tmp->id == sp)
		d_tmp = sp_intersect(pos, ray, obj_tmp->type.sp);
	else if (obj_tmp->id == sq)
		d_tmp = sq_intersect(pos, ray, obj_tmp->type.sq);
	else if (obj_tmp->id == tr)
		d_tmp = tr_intersect(pos, ray, obj_tmp->type.tr);
	else if (obj_tmp->id == cy)
		d_tmp = cy_intersect(pos, ray, obj_tmp->type.cy);
	else if (obj_tmp->id == pl)
		d_tmp = pl_intersect(obj_tmp->type.pl->orien, pos,
								obj_tmp->type.pl->pos, ray);
	return (d_tmp);
}

t_color	*pixel_color(t_vec **intersect, t_rt_scene *scene, t_camera *cam,
							int obj_index)
{
	t_color	*rgb;
	t_obj	*obj;
	int		i;

	rgb = NULL;
	i = 0;
	obj = scene->obj;
	if (obj_index == -1)
	{
		free(*intersect);
		*intersect = NULL;
		return (gen_color(0, 0, 0));
	}
	while (i < obj_index)
	{
		obj = obj->next;
		i++;
	}
	rgb = calculate_final_color(scene, intersect, obj, cam);
	return (rgb);
}

t_color	*ray_intersect(t_rt_scene *scene, t_vec *ray, t_camera *cam)
{
	t_less_vars	vars;
	double		d;
	t_obj		*obj_tmp;
	int			obj_index;
	t_vec		*intersect;

	d = INFINITY;
	obj_tmp = scene->obj;
	obj_index = -1;
	vars.i = -1;
	while (obj_tmp != NULL)
	{
		vars.i++;
		vars.dist = check_obj_intersect(obj_tmp, ray, cam->pos, vars.dist);
		if (vars.dist == INSIDE_OBJ)
			return (NULL);
		if (vars.dist < d && vars.dist > EPSILON)
		{
			d = vars.dist;
			obj_index = vars.i;
		}
		obj_tmp = obj_tmp->next;
	}
	intersect = find_point(cam->pos, ray, d);
	return (pixel_color(&intersect, scene, cam, obj_index));
}
