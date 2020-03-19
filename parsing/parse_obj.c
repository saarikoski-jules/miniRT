
#include "object.h"
#include "parse.h"
#include "libft.h"
#include "error.h"

t_sp	*get_sphere(char *line, size_t *i)
{
	t_sp	*sphere;

	sphere = (t_sp*)malloc(sizeof(t_sp));
	if (!sphere)
		error_exit_errno();
	sphere->pos = get_vec(line, i);
	*i += ft_strmatch(line + *i, " ");
	sphere->dia = get_float(line, i);
	if (sphere->dia < 0.0)
		error_exit_msg(C_INVALID_SP, E_INVALID_SP);
	return (sphere);
}

t_pl	*get_plane(char *line, size_t *i)
{
	t_pl *plane;

	plane = (t_pl*)malloc(sizeof(t_pl));
	if (!plane)
		error_exit_errno();
	plane->pos = get_vec(line, i);
	plane->orien = get_vec(line, i);
	validate_orien(plane->orien);
	return (plane);
}

t_sq	*get_square(char *line, size_t *i)
{
	t_sq	*square;

	square = (t_sq*)malloc(sizeof(t_sq));
	if (!square)
		error_exit_errno();
	square->pos = get_vec(line, i);
	square->orien = get_vec(line, i);
	validate_orien(square->orien);
	square->side = get_float(line, i);
	if (square->side < 0.0)
		error_exit_msg(C_INVALID_SQ, E_INVALID_SQ);
	return (square);
}

t_cy	*get_cylinder(char *line, size_t *i)
{
	t_cy	*cylinder;

	cylinder = (t_cy*)malloc(sizeof(t_cy));
	if (!cylinder)
		error_exit_errno();
	cylinder->pos = get_vec(line, i);
	cylinder->orien = get_vec(line, i);
	validate_orien(cylinder->orien);
	cylinder->dia = get_float(line, i);
	cylinder->h = get_float(line, i);
	if (cylinder->dia < 0.0 || cylinder->h < 0.0)
		error_exit_msg(C_INVALID_CY, E_INVALID_CY);
	return (cylinder);
}

t_tr	*get_triangle(char *line, size_t *i)
{
	t_tr	*triangle;

	triangle = (t_tr*)malloc(sizeof(t_tr));
	if (!triangle)
		error_exit_errno();
	triangle->point1 = get_vec(line, i);
	triangle->point2 = get_vec(line, i);
	triangle->point3 = get_vec(line, i);
	return (triangle);
}
