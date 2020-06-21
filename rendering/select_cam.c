/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   select_cam.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 13:08:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 16:44:34 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (i < 0)
		i = 0;
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
	t_camera	*cam_orig;
	t_camera	*cam_cur;
	t_cam_info	*cam_data;
	int			i;

	cam_orig = data->scene->cam;
	cam_cur = NULL;
	i = data->i;
	if (key == KEYCODE_RIGHT)
	{
		if (i < data->cam_amt)
			i++;
	}
	else if (key == KEYCODE_LEFT)
	{
		if (i > 0)
			i--;
	}
	cam_cur = find_cam(cam_orig, i);
	cam_data = gen_cam_data(data->scene, cam_cur);
	render_image(data, cam_data);
	free(cam_data->cam_right);
	free(cam_data->cam_up);
	free(cam_data->screen);
	free(cam_data);
	return (i);
}