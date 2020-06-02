
#include "parse.h"
#include "error.h"
#include "libft.h"

void	get_object_type(char *line, size_t *i, t_obj **obj)
{
	if (ft_strncmp(line, "sp", 2) == 0)
	{
		(*obj)->id = sp;
		(*obj)->type.sp = get_sphere(line, i);
		// ft_printf("sphere position: (%f, %f, %f)\nsphere diameter: %f\n", (*obj)->type.sp->pos->x, (*obj)->type.sp->pos->y, (*obj)->type.sp->pos->z, (*obj)->type.sp->dia);

	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		(*obj)->id = pl;
		(*obj)->type.pl = get_plane(line, i);

		// ft_printf("plane position: (%f, %f, %f)\nplane orientation: (%f, %f, %f)\n", (*obj)->type.pl->pos->x, (*obj)->type.pl->pos->y, (*obj)->type.pl->pos->z, (*obj)->type.pl->orien->x, (*obj)->type.pl->orien->y, (*obj)->type.pl->orien->z);
	}
	else if (ft_strncmp(line, "sq", 2) == 0)
	{
		(*obj)->id = sq;
		(*obj)->type.sq = get_square(line, i);
		// ft_printf("square position: (%f, %f, %f)\nsquare orientation: (%f, %f, %f)\nlength of side: %f\n", (*obj)->type.sq->pos->x, (*obj)->type.sq->pos->y, (*obj)->type.sq->pos->z, (*obj)->type.sq->orien->x, (*obj)->type.sq->orien->y, (*obj)->type.sq->orien->z, (*obj)->type.sq->side);

	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		(*obj)->id = cy;
		(*obj)->type.cy = get_cylinder(line, i);

		// ft_printf("cylinder position: (%f, %f, %f)\ncylinder orientation: (%f, %f, %f)\ndiameter: %f\nheight: %f\n", (*obj)->type.cy->pos->x, (*obj)->type.cy->pos->y, (*obj)->type.cy->pos->z, (*obj)->type.cy->orien->x, (*obj)->type.cy->orien->y, (*obj)->type.cy->orien->z, (*obj)->type.cy->dia, (*obj)->type.cy->h);

	}
	else if (ft_strncmp(line, "tr", 2) == 0)
	{
		(*obj)->id = tr;
		(*obj)->type.tr = get_triangle(line, i);

		// ft_printf("triangle corner1: (%f, %f, %f)\ntriangle corner2: (%f, %f, %f)\ntriangle corner3: (%f, %f, %f)\n", (*obj)->type.tr->point1->x, (*obj)->type.tr->point1->y, (*obj)->type.tr->point1->z, (*obj)->type.tr->point2->x, (*obj)->type.tr->point2->y, (*obj)->type.tr->point2->z, (*obj)->type.tr->point3->x, (*obj)->type.tr->point3->y, (*obj)->type.tr->point3->z);
	}
}

t_obj	*get_object(char *line)
{
	t_obj *obj;
	size_t i;

	i = 2;
	obj = (t_obj*)malloc(sizeof(t_obj));
	if (!obj)
		error_exit_errno();
	get_object_type(line, &i, &obj);
	obj->color = get_color(line, &i);
	// ft_printf("color: (%d, %d, %d)\n\n", obj->color->r, obj->color->g, obj->color->b);
	if (line[i] != '\0')
		error_exit_msg(C_INVALID_OBJ, E_INVALID_OBJ);
	obj->next = NULL;
	return (obj);
}

t_obj	*add_object(char *line, t_obj *first_obj)
{
	t_obj *new_obj;
	t_obj *cur;

	cur = first_obj;
	new_obj = get_object(line);
	if (first_obj == NULL)
		first_obj = new_obj;
	else
	{
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = new_obj;
	}
	return (first_obj);
}
