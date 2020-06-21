/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 17:57:23 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 17:59:03 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parse.h"

t_camera	*get_camera(char *line)
{
	size_t		i;
	t_camera	*cam;

	cam = (t_camera *)e_malloc(sizeof(t_camera));
	if (cam == NULL)
		error_exit_errno();
	i = 0;
	cam->pos = get_vec(line, &i);
	cam->orien = get_vec(line, &i);
	validate_orien(&cam->orien);
	cam->fov = get_int(line, &i);
	if (cam->fov <= 0 || cam->fov >= 180)
		error_exit_msg(C_INVALID_FOV, E_INVALID_FOV);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_CAM, E_INVALID_CAM);
	cam->next = NULL;
	return (cam);
}

t_camera	*add_camera(char *line, t_camera *first_camera)
{
	t_camera *new_cam;
	t_camera *cur;

	cur = first_camera;
	new_cam = get_camera(line);
	if (first_camera == NULL)
		first_camera = new_cam;
	else
	{
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_cam;
	}
	return (first_camera);
}
