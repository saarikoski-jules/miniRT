/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 18:03:38 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 17:48:24 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "parse.h"
#include "libft.h"
#include "error.h"

t_sp	*get_sphere(char *line, size_t *i)
{
	t_sp	*sphere;

	sphere = (t_sp*)e_malloc(sizeof(t_sp));
	sphere->pos = get_vec(line, i);
	*i += ft_strmatch(line + *i, " ");
	sphere->dia = get_float(line, i);
	if (sphere->dia < 0.0)
		error_exit_msg(C_INVALID_SP, E_INVALID_SP);
	sphere->r = sphere->dia * 0.5;
	return (sphere);
}

t_pl	*get_plane(char *line, size_t *i)
{
	t_pl *plane;

	plane = (t_pl*)e_malloc(sizeof(t_pl));
	plane->pos = get_vec(line, i);
	plane->orien = get_vec(line, i);
	validate_orien(&plane->orien);
	return (plane);
}

t_tr	*get_triangle(char *line, size_t *i)
{
	t_tr	*triangle;
	t_vec	*ba;
	t_vec	*ca;
	t_vec	*normal;

	triangle = (t_tr *)e_malloc(sizeof(t_tr));
	triangle->point1 = get_vec(line, i);
	triangle->point2 = get_vec(line, i);
	triangle->point3 = get_vec(line, i);
	ba = substract_vectors(triangle->point2, triangle->point1);
	ca = substract_vectors(triangle->point3, triangle->point1);
	normal = get_cross_product(ba, ca);
	triangle->orien = set_vec_len(normal, 1.0);
	free(ba);
	free(ca);
	free(normal);
	return (triangle);
}
