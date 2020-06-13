/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   select_cam.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 13:08:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/13 14:54:48 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "xevents.h"
#include "render.h"
#include <stdlib.h>

int			get_cam_amt(t_camera *cam_head)
{
	int			amt;
	t_camera	*cur;

	amt = 0;
	cur = cam_head;
	while (cur->next != NULL)
	{
		amt++;
		cur = cur->next;
	}
	return (amt);
}

t_camera	*find_cam(t_camera *cam_orig, int i)
{
	t_camera	*cam_new;
	int			j;
	
	j = 0;
	cam_new = cam_orig;
	if (i < 0) //return error, set to 1 and return first camera
		i = 0; //return (NULL);
	if (i == 0)
		return (cam_orig);
	while (j < i && cam_new->next != NULL)
	{
		cam_new = cam_new->next;
		j++;
	}
	return (cam_new);
}

int			select_cam(int key, t_mlx_data *data)
{
	t_rt_scene	*scene;
	t_camera	*cam_orig;
	t_camera	*cam_cur;
	int			i;
	
	scene = data->scene;
	cam_orig = scene->cam;
	cam_cur = NULL;
	i = data->i;
	if (cam_orig == NULL)
		return (-1);
	if (key == KEYCODE_RIGHT)//65363 for windows //TODO: segfaults hard in any case
	{
		if (i < data->cam_amt)
			i++; //only do this if camera is found successfully
	}
	else if (key == KEYCODE_LEFT)//65361 for windows
	{
		if (i > 0) //TODO: segfaults when pressing back first
			i--; //only do this if camera is found successfully
	}
	cam_cur = find_cam(cam_orig, i);
	trace(data, cam_cur, -1);
	return (i);
}