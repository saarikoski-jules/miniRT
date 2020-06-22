/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slerp.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 14:09:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 15:57:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "manage_cameras.h"
#include "error.h"
#include "xevents.h"
#include "libft.h"//
#include <stdio.h>//

t_vec *slerp(t_vec *original_orien, t_vec *rotate_dir, double t)
{
	printf("%f, %f, %f\n", rotate_dir->x, rotate_dir->y, rotate_dir->x);
	(void)t;
	return(original_orien);


    // Only unit quaternions are valid rotations.
    // Normalize to avoid undefined behavior.


	//NORMALIZE VECTORS


    // Compute the cosine of the angle between the two vectors.
    double dot = get_dot_product(original_orien, rotate_dir);

    // If the dot product is negative, slerp won't take
    // the shorter path. Note that v1 and -v1 are equivalent when
    // the negation is applied to all four components. Fix by 
    // reversing one quaternion.
    if (dot < 0.0f) {
        v1 = -v1;
        dot = -dot;
    }

    const double DOT_THRESHOLD = 0.9995;
    if (dot > DOT_THRESHOLD) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.

        Quaternion result = v0 + t*(v1 - v0);
        result.normalize();
        return result;
    }

    // Since dot is in range [0, DOT_THRESHOLD], acos is safe
    double theta_0 = acos(dot);        // theta_0 = angle between input vectors
    double theta = theta_0*t;          // theta = angle between v0 and result
    double sin_theta = sin(theta);     // compute this value only once
    double sin_theta_0 = sin(theta_0); // compute this value only once

    double s0 = cos(theta) - dot * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
    double s1 = sin_theta / sin_theta_0;

    return (s0 * v0) + (s1 * v1);


}

void	rotate_camera(int key, t_mlx_data **data, int cam_index)
{
	t_camera	*cam;
	t_camera	*cam_new;
	t_cam_info	*cam_info;
	t_vec		*rotate_dir;
	t_vec		*new_orien;
	double		t;

	rotate_dir = NULL;
	ft_printf("(*data)aaa %p, %d\n", (*data)->scene, cam_index);
	cam = find_cam((*data)->scene->cam, cam_index);
	if (key == KEYCODE_UP)
	{
		t = 0.2;
		t_vec *rotate_dir = gen_coord(0, 1, 0);
		cam_new = (t_camera *)e_malloc(sizeof(t_camera));
		cam_new->pos = cam->pos;
		cam_new->fov = cam->fov;
		if ((*data)->cur_orien == NULL)
			new_orien = slerp(cam->orien, rotate_dir, t);
		else
		{
			new_orien = slerp((*data)->cur_orien, rotate_dir, t);
		}
		cam_new->orien = new_orien;
		cam_new->next = NULL;
		cam_info = gen_cam_data((*data)->scene, cam_new);
		
		render_image(*data, cam_info);
		free(cam);
		free(cam_new);
		free(cam_info);
		free(rotate_dir);
		free((*data)->cur_orien);
		(*data)->cur_orien = new_orien;
	}
}
