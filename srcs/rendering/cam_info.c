/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cam_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 16:14:27 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 19:09:43 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "error.h"
#include <math.h>

static t_screen_details	*screen_details(t_rt_scene *scene, t_camera *cam)
{
	t_screen_details	*screen;
	int					fov_vert;

	fov_vert = 60;
	screen = (t_screen_details *)e_malloc(sizeof(t_screen_details));
	screen->aspect_ratio = ((double)scene->res->res_x /
							(double)scene->res->res_y);
	screen->len_x = tan((cam->fov / 2) * (M_PI / 180));
	screen->len_y = tan((fov_vert / 2) * (M_PI / 180));
	screen->inc_x = 1.0 / scene->res->res_x;
	screen->inc_y = 1.0 / scene->res->res_y;
	return (screen);
}

t_cam_info				*gen_cam_data(t_rt_scene *scene, t_camera *cam)
{
	t_cam_info	*cam_data;
	t_vec		*cam_right;
	t_vec		*world_up;

	cam_data = (t_cam_info *)e_malloc(sizeof(t_cam_info));
	cam_data->cam = cam;
	cam_data->screen = screen_details(scene, cam);
	world_up = gen_coord(0, 1, 0);
	if (cam->orien->x == 0.0 && cam->orien->z == 0.0)
	{
		if (cam->orien->y == -1.0)
			cam_right = gen_coord(1, 0, 0);
		else
			cam_right = gen_coord(-1, 0, 0);
	}
	else
		cam_right = get_cross_product(cam->orien, world_up);
	cam_data->cam_right = set_vec_len(cam_right, 1.0);
	cam_data->cam_up = get_cross_product(cam_data->cam_right, cam->orien);
	free(cam_right);
	free(world_up);
	return (cam_data);
}
