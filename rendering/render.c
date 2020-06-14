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

t_color *ray_intersect(t_rt_scene *scene, t_vec *ray, t_camera *cam)
{
	t_obj *tmp;
	double d;
	double d_tmp;
	unsigned int	color;
	color = 0;
	d = 1.0/0.0; 
	d_tmp = -1.0;
	tmp = scene->obj;
	t_vec *n;
	n = gen_coord(0, 0, 0);
	if (tmp == NULL)
		return (0);
	t_color *rgb;
	rgb = (t_color *)e_malloc(sizeof(t_color));
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
	while(tmp != NULL)
	{

		if (tmp != NULL)
		{
			if (tmp->id == sp)
			{

				d_tmp = sp_intersect(cam->pos, ray, tmp->type.sp);
			}
			else if (tmp->id == sq)
			{
				// if (get_dot_product(cam->orien, tmp->type.sq->orien) < 0)
					// ft_printf("breaks? %f\n", get_dot_product(cam->orien, tmp->type.sq->orien));
				d_tmp = sq_intersect(cam->pos, ray, tmp->type.sq);
			}
			else if (tmp->id == tr)
			{
				d_tmp = tr_intersect(cam->pos, ray, tmp->type.tr);
			}
			else if (tmp->id == cy)
			{
				d_tmp = cy_intersect(cam->pos, ray, tmp->type.cy);
				// if (d_tmp != 0.0 && d_tmp != NO_INTERSECT)
			}
			else if (tmp->id == pl)
			{
				d_tmp = pl_intersect(tmp->type.pl->orien, cam->pos, tmp->type.pl->pos, ray);
			
			}
			if (d_tmp == -10.0 || d_tmp == INSIDE_OBJ) //change
			{
				return (NULL);
			}
		}

		if (d_tmp < d && d_tmp > EPSILON)
		{
			// if (tmp->id == sq)
				// printf("sq: %f\n", d_tmp);
			// ft_printf("type: %d\nobj->color (%d, %d, %d)\n", tmp->id, tmp->color->r, tmp->color->g, tmp->color->b);
			
			// ft_printf("aa\n");
			d = d_tmp;
			rgb = calculate_final_color(scene, ray, tmp->color, d, tmp, n, cam);  //fix this so it's only ran once per pixel??
			// color = translate_color(rgb);
		}
		tmp = tmp->next;
	}
	return (rgb);
}

