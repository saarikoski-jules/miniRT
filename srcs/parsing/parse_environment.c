/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_environment.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:41:56 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 17:58:45 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parse.h"

t_resolution	*get_resolution(char *line)
{
	t_resolution	*res;
	size_t			i;

	i = 0;
	res = (t_resolution*)e_malloc(sizeof(t_resolution));
	res->res_x = get_int(line, &i);
	res->res_y = get_int(line, &i);
	if (res->res_x < 0 || res->res_y < 0)
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_RES, E_INVALID_RES);
	return (res);
}

t_ambiance		*get_ambiance(char *line)
{
	t_ambiance	*amb;
	size_t		i;

	amb = (t_ambiance*)e_malloc(sizeof(t_ambiance));
	i = 0;
	amb->ratio = get_float(line, &i);
	if (amb->ratio > 1.0 || amb->ratio < 0.0)
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	amb->color = get_color(line, &i);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_AMB, E_INVALID_AMB);
	return (amb);
}

t_light			*get_light(char *line)
{
	size_t	i;
	t_light	*light;

	light = (t_light *)e_malloc(sizeof(t_camera));
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
	light->next = NULL;
	return (light);
}

t_light			*add_light(char *line, t_light *first_light)
{
	t_light *new_light;
	t_light *cur;

	cur = first_light;
	new_light = get_light(line);
	if (first_light == NULL)
		first_light = new_light;
	else
	{
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_light;
	}
	return (first_light);
}
