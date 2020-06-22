/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 12:21:52 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 12:14:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "vec.h"
#include "rt.h"
#include <math.h>
#include <stdlib.h>

static t_vec	*cy_shaft_normal(t_cy *cy, t_vec *intersect, double len)
{
	double	len_z;
	t_vec	*v_len_z;
	t_vec	*z;
	t_vec	*normal;

	len_z = sqrt(pow(len, 2) - pow(cy->r, 2));
	v_len_z = set_vec_len(cy->orien, len_z);
	z = add_vectors(cy->end1, v_len_z);
	normal = substract_vectors(intersect, z);
	free(v_len_z);
	free(z);
	return (normal);
}

static t_vec	*cy_normal(t_cy *cy, t_vec *intersect)
{
	t_vec	*v_len;
	double	len;
	t_vec	*v_up;
	t_vec	*origin;
	t_vec	*orien_opp;

	v_up = substract_vectors(intersect, cy->end2);
	if (det_len_vec(v_up) <= cy->r)
	{
		free(v_up);
		return (gen_coord(cy->orien->x, cy->orien->y, cy->orien->z));
	}
	v_len = substract_vectors(intersect, cy->end1);
	len = det_len_vec(v_len);
	free(v_len);
	free(v_up);
	if (len <= cy->r)
	{
		origin = gen_coord(0.0, 0.0, 0.0);
		orien_opp = substract_vectors(origin, cy->orien);
		free(origin);
		return (orien_opp);
	}
	return (cy_shaft_normal(cy, intersect, len));
}

static t_vec	*pl_normal(t_vec *orien, t_vec *obj_pos, t_camera *cam)
{
	t_vec	*normal;
	t_vec	*oc;
	t_vec	*oc_u;

	oc = substract_vectors(cam->pos, obj_pos);
	oc_u = set_vec_len(oc, 1.0);
	if (get_dot_product(oc_u, orien) < 0)
		normal = gen_coord(-orien->x, -orien->y, -orien->z);
	else
		normal = gen_coord(orien->x, orien->y, orien->z);
	free(oc);
	free(oc_u);
	return (normal);
}

t_vec			*calculate_normal(t_obj *obj, t_vec *intersect, t_camera *cam)
{
	t_vec	*normal;
	t_vec	*normal_u;

	if (obj->id == cy)
		normal = cy_normal(obj->type.cy, intersect);
	else if (obj->id == sp)
		normal = substract_vectors(intersect, obj->type.sp->pos);
	else if (obj->id == pl)
		normal = pl_normal(obj->type.pl->orien, obj->type.pl->pos, cam);
	else if (obj->id == tr)
		normal = pl_normal(obj->type.tr->orien, obj->type.tr->point1, cam);
	else
		normal = pl_normal(obj->type.sq->orien, obj->type.sq->pos, cam);
	normal_u = set_vec_len(normal, 1);
	free(normal);
	return (normal_u);
}
