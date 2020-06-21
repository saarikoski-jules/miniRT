/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 18:04:37 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 18:07:49 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "error.h"
#include "parse.h"

static void	det_cy_data(t_cy **cy)
{
	t_vec *mov;
	t_vec *base;

	base = gen_coord(0, 0, -1);
	(*cy)->r = (*cy)->dia * 0.5;
	mov = set_vec_len((*cy)->orien, (*cy)->h * 0.5);
	(*cy)->end2 = add_vectors((*cy)->pos, mov);
	(*cy)->end1 = substract_vectors((*cy)->pos, mov);
	free(mov);
	(*cy)->q = determine_quaternion(base, (*cy)->orien);
	free(base);
}

t_cy		*get_cylinder(char *line, size_t *i)
{
	t_cy	*cylinder;

	cylinder = (t_cy *)e_malloc(sizeof(t_cy));
	cylinder->pos = get_vec(line, i);
	cylinder->orien = get_vec(line, i);
	validate_orien(&cylinder->orien);
	cylinder->dia = get_float(line, i);
	cylinder->h = get_float(line, i);
	if (cylinder->dia < 0.0 || cylinder->h < 0.0)
		error_exit_msg(C_INVALID_CY, E_INVALID_CY);
	det_cy_data(&cylinder);
	return (cylinder);
}
