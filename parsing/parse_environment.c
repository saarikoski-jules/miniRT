

#include "error.h"
#include "parse.h"//
#include "rt.h"//
#include "libft.h"

// #include <stdlib.h>

void get_resolution(char *line)
{
	t_resolution	*res;
	size_t			i;

	i = 0;
	res = (t_resolution*)malloc(sizeof(t_resolution));
	res->res_x = get_int(line, &i);
	res->res_y = get_int(line, &i);
	if (res->res_x < 0 || res->res_y < 0)
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	// ft_printf("Resolution:\nres_x %d, res_y %d\n\n", res->res_x, res->res_y);
}

void get_ambiance(char *line)
{
	t_ambiance	*amb;
	size_t		i;

	amb = (t_ambiance*)malloc(sizeof(t_ambiance));
	i = 0;
	amb->ratio = get_float(line, &i);
	if (amb->ratio > 1.0 || amb->ratio < 0.0)
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	amb->color = get_color(line, &i);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	// ft_printf("Ambiance:\nratio: %f\nr: %d\ng: %d\nb: %d\n\n", amb->ratio, amb->color->r, amb->color->g, amb->color->b);
}

void get_light(char *line)
{
	size_t		i;
	t_light	*light;

	light = malloc(sizeof(t_camera));
	if (light == NULL)
		error_exit_errno();
	i = 0;
	light->pos = get_vec(line, &i);
	light->brightness = get_float(line, &i);
	if (light->brightness > 1 || light->brightness < 0)
		error_exit_msg(C_INVALID_LIGHT, E_INVALID_LIGHT);
	light->color = get_color(line, &i);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_LIGHT, E_INVALID_LIGHT);
	// ft_printf("Light:\ncoords, x: %f, y: %f, z: %f\nbrightness: %f\ncolor: r: %d, g: %d, b: %d\n\n", light->pos->x, light->pos->y,  light->pos->z, light->brightness, light->color->r, light->color->g, light->color->b);
}

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
	cam->fov = get_int(line, &i);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_CAM, E_INVALID_CAM);

	// ft_printf("Camera:\n\
	Pos:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\
	Orient:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\
	Fov: %d\n\n",
	// cam->pos->x, cam->pos->y, cam->pos->z,
	// cam->orien->x, cam->orien->y, cam->orien->z,
	// cam->fov);
}

