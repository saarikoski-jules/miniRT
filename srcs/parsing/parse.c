/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 16:02:26 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 17:45:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "parse.h"
#include <fcntl.h>

void		parse_line(char *line, t_rt_scene **scene)
{
	if (line[0] == '#')
		return ;
	else if (line[0] == 'R' && (*scene)->res == NULL)
		(*scene)->res = get_resolution(line + 1);
	else if (line[0] == 'A' && (*scene)->amb == NULL)
		(*scene)->amb = get_ambiance(line + 1);
	else if (ft_strncmp(line, "l ", 2) == 0)
		(*scene)->light = add_light(line + 1, (*scene)->light);
	else if (ft_strncmp(line, "c ", 2) == 0)
		(*scene)->cam = add_camera(line + 1, (*scene)->cam);
	else if (ft_strncmp(line, "sp", 2) == 0 || ft_strncmp(line, "pl", 2) == 0
		|| ft_strncmp(line, "sq", 2) == 0 || ft_strncmp(line, "cy", 2) == 0
		|| ft_strncmp(line, "tr", 2) == 0)
		(*scene)->obj = add_object(line, (*scene)->obj);
	else
		error_exit_msg(C_PARSE, E_PARSE);
}

void		get_input(char *path, t_rt_scene **scene)
{
	int			fd;
	int			ret;
	char		*line;

	validate_file(path);
	ret = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_strncmp(line, "\0", 1) != 0)
			parse_line(line, scene);
		free(line);
	}
	close(fd);
}

t_rt_scene	*get_scene(char *path)
{
	t_rt_scene *scene;

	scene = (t_rt_scene*)e_malloc(sizeof(t_rt_scene));
	scene->res = NULL;
	scene->amb = NULL;
	scene->light = NULL;
	scene->cam = NULL;
	scene->obj = NULL;
	get_input(path, &scene);
	if (scene->res == NULL)
		error_exit_msg(C_NO_RES, E_NO_RES);
	if (scene->amb == NULL)
		error_exit_msg(C_NO_AMB, E_NO_AMB);
	if (scene->cam == NULL)
		error_exit_msg(C_NO_CAM, E_NO_CAM);
	return (scene);
}
