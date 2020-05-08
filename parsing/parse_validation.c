/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 15:46:03 by jvisser       #+#    #+#                 */
/*   Updated: 2020/05/08 10:56:14 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "rt.h"
#include "libft.h"

void	validate_orien(t_vec *orien)
{
	if (orien->x < -1 || orien->x > 1
	|| orien->y < -1 || orien->y > 1
	|| orien->z < -1 || orien->z > 1)
		error_exit_msg(C_INVALID_ORIEN_VEC, E_INVALID_ORIEN_VEC);
}

void	validate_fov(int fov)
{
	if (fov < 0 || fov > 180)
		error_exit_msg(C_INVALID_FOV, E_INVALID_FOV);
}

// void	validate_color(t_color *color)
// {
// 	if ((color->r > 255 || color->r < 0)
// 	||	(color->g > 255 || color->g < 0)
// 	||	(color->b > 255 || color->b < 0))
// 		error_exit_msg(C_INVALID_COLOR, E_INVALID_COLOR);
// }

void	validate_file(char *path)
{
	char **split;
	char *extension;
	size_t i;

	i = 0;
	split = ft_split(path, '.');
	while (split[i] != NULL)
	{
		extension = split[i];
		i++;
	}
	if (ft_strncmp(extension, "rt", 3) != 0)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
}
