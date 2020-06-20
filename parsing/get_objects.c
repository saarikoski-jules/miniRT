
#include "parse.h"
#include "error.h"
#include "libft.h"

void	get_object_type(char *line, size_t *i, t_obj **obj)
{
	if (ft_strncmp(line, "sp", 2) == 0)
	{
		(*obj)->id = sp;
		(*obj)->type.sp = get_sphere(line, i);
	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		(*obj)->id = pl;
		(*obj)->type.pl = get_plane(line, i);
	}
	else if (ft_strncmp(line, "sq", 2) == 0)
	{
		(*obj)->id = sq;
		(*obj)->type.sq = get_square(line, i);
	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		(*obj)->id = cy;
		(*obj)->type.cy = get_cylinder(line, i);

	}
	else if (ft_strncmp(line, "tr", 2) == 0)
	{
		(*obj)->id = tr;
		(*obj)->type.tr = get_triangle(line, i);
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
			cur = cur->next;
		cur->next = new_obj;
	}
	return (first_obj);
}
