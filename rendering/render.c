#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "quaternion.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//
#include <parse.h>


// 	// ☺

//TODO: fisheye lens for 180 fov
//TODO: if two items are on the exact same 2D plane, which one displays? Right now the one mentioned earlier in the .rt file is displayed
//TODO: square is not visible if your camera and square orientation are the same
//TODO: cylinders break when seen more from the direction of the endcaps
//TODO: cylinder is rendered slightly wider than it's meant to
//TODO: what happens when any object is on top of me
//TODO: make sure any invalid arguments aren't accepted. Make sure --saved is the only extra thing that works
//TODO: image flipped when looking behind. Is this bad?
//TODO: quaternions break when camera pointing directly into 0,0,-1 or 0,0,1.
//TODO: Bugfixes -> squares break with specific orientation (0,0,-1)
//TODO: is there a random segfault with file breaks_cy.rt

t_color *gen_color(int r, int g, int b) //TODO: move to utils
{
	t_color *rgb;

	rgb = (t_color *)e_malloc(sizeof(t_color));
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

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
		
t_color *ray_intersect(t_rt_scene *scene, t_vec *ray, t_camera *cam)
{
	t_obj	*obj_tmp;
	double	d;
	double	d_tmp;
	t_color *rgb;

	d = INFINITY;
	d_tmp = NO_INTERSECT;
	obj_tmp = scene->obj;
	rgb = gen_color(0, 0, 0); //TODO: will leak
	if (obj_tmp == NULL)
		return (NULL);
	while (obj_tmp != NULL)
	{
		d_tmp = check_obj_intersect(obj_tmp, ray, cam->pos, d_tmp);
		if (d_tmp == -10.0 || d_tmp == INSIDE_OBJ) //change
			return (NULL);
		if (d_tmp < d && d_tmp > EPSILON)
		{
			d = d_tmp;
			rgb = calculate_final_color(scene, ray, obj_tmp->color, d, obj_tmp, cam);  //fix this so it's only ran once per pixel??
		}
		obj_tmp = obj_tmp->next;
	}
	// if (!rgb) //TODO: make sure rgb is always allocated or null
	return (rgb);
}

