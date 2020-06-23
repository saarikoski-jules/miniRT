/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 12:19:51 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 17:46:43 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "rt.h"
#include "libft.h"

void	validate_orien(t_vec **orien)
{
	t_vec *orien_u;

	if ((*orien)->x < -1 || (*orien)->x > 1
	|| (*orien)->y < -1 || (*orien)->y > 1
	|| (*orien)->z < -1 || (*orien)->z > 1)
		error_exit_msg(C_INVALID_ORIEN_VEC, E_INVALID_ORIEN_VEC);
	orien_u = set_vec_len(*orien, 1.0);
	free(*orien);
	*orien = orien_u;
}

void	validate_fov(int fov)
{
	if (fov < 0 || fov > 180)
		error_exit_msg(C_INVALID_FOV, E_INVALID_FOV);
}

void	validate_file(char *path)
{
	char	**split;
	char	*extension;
	size_t	i;

	i = 0;
	split = ft_split(path, '.');
	while (split[i] != NULL)
	{
		extension = split[i];
		i++;
	}
	if (ft_strncmp(extension, "rt", 3) != 0)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
