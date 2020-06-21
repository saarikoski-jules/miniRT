#include "render.h"
#include "collision_utils.h"
#include <math.h>

// 	// ☺

//TODO: square is not visible if your camera and square orientation are the same
//TODO: cylinders break when seen more from the direction of the endcaps
//TODO: what happens when any object is on top of me
//TODO: Bugfixes -> squares break with specific orientation (0,0,-1)
//TODO: is there a random segfault with file breaks_cy.rt


double check_obj_intersect(t_obj *obj_tmp, t_vec *ray, t_vec *pos, double d_tmp)
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
		d_tmp = pl_intersect(obj_tmp->type.pl->orien, pos, obj_tmp->type.pl->pos, ray);
	return (d_tmp);
}

t_color *pixel_color(t_camera *cam, t_vec *ray, double d, t_rt_scene *scene, t_obj **obj_head, int obj_index)
{
	t_vec *intersect;
	t_color *rgb;
	t_obj *obj;
	int i;

	rgb = NULL;
	i = 0;
	obj = *obj_head;
	if (obj_index == -1)
		return (gen_color(0,0,0));
	while (i < obj_index)
	{
		obj = obj->next;
		i++;
	}
	intersect = find_point(cam->pos, ray, d);
	rgb = calculate_final_color(scene, &intersect, obj, cam);
	return (rgb);
}

t_color *ray_intersect(t_rt_scene *scene, t_vec *ray, t_camera *cam)
{
	double	d_tmp;
	double	d;
	t_obj	*obj_tmp;
	t_color *rgb;
	int		obj_index;
	int		i;

	d = INFINITY;
	obj_tmp = scene->obj;
	rgb = NULL;
	obj_index = -1;
	i = -1;
	while (obj_tmp != NULL)
	{
		i++;
		d_tmp = check_obj_intersect(obj_tmp, ray, cam->pos, d_tmp);
		if (d_tmp == INSIDE_OBJ) //TODO: hopefully nothing returns -10 anymore//change
			return (NULL);
		if (d_tmp < d && d_tmp > EPSILON)
		{
			d = d_tmp;
			obj_index = i;
		}
		obj_tmp = obj_tmp->next;
	}
	rgb = pixel_color(cam, ray, d, scene, &scene->obj, obj_index);
	return (rgb);
}

//TODO: test with no objects (*obj == null)
