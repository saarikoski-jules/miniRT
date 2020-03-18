/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:00:30 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 16:02:14 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "error.h"
#include "libft.h"
#include "parse.h"

void	get_camera(char *line)
{
	size_t		i;
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	if (cam == NULL)
		error_exit_errno();
	i = 0;
	cam->pos = get_vec(line, &i);
	cam->orien = get_vec(line, &i);
	validate_orien(cam->orien);
	i += ft_strmatch(&line[i], " ");
	cam->fov = get_int(line, &i);
	i += ft_strmatch(&line[i], " ");
	if (line[i] && line[i + 1])
		error_exit_msg(C_INVALID_CAM, E_INVALID_CAM);

	ft_printf("Camera:\n\
	Pos:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\
	Orient:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\
	Fov: %d\n",
	cam->pos->x, cam->pos->y, cam->pos->z,
	cam->orien->x, cam->orien->y, cam->orien->z,
	cam->fov);
}
