/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/18 17:03:13 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "render.h"

void print_scene(t_rt_scene *scene)
{
	t_light *cur_light;
	t_camera *cur_cam;
	t_obj *cur_obj;
	size_t i;

	cur_light = scene->light;
	cur_cam = scene->cam;
	cur_obj = scene->obj;
	ft_printf("resolution: (%d, %d)\n\nambiance:\n\tratio:\t%f\n\tcolor\t(%d, %d, %d)\n\n", scene->res->res_x, scene->res->res_y, scene->amb->ratio, scene->amb->color->r, scene->amb->color->g, scene->amb->color->b);

	ft_printf("lights:\n");
	i = 1;
	while (cur_light != NULL)
	{
		if (cur_light != NULL)
		{
			ft_printf("\tlight%d:\n\tposition:\t(%f, %f, %f)\n\tbrightness:\t%f\n\tcolor:\t\t(%d, %d, %d)\n\n", i, cur_light->pos->x, cur_light->pos->y, cur_light->pos->z, cur_light->brightness, scene->light->color->r, scene->light->color->g, scene->light->color->b);
			cur_light = cur_light->next;
			i++;
		}
	}

	ft_printf("cameras:\n");
	i = 1;
	while (cur_cam != NULL)
	{
		if (cur_cam != NULL)
		{
			ft_printf("\tcam%d:\n\tposition:\t(%f, %f, %f)\n\torientation:\t(%f, %f, %f)\n\tfov:\t\t%d\n\n", i, cur_cam->pos->x, cur_cam->pos->y, cur_cam->pos->z, cur_cam->orien->x, cur_cam->orien->y, cur_cam->orien->z, cur_cam->fov);
			cur_cam = cur_cam->next;
			i++;
		}
	}
	ft_printf("objects:\n");
	i = 1;
	while (cur_obj != NULL)
	{
		if (cur_obj != NULL)
		{
			ft_printf("\tobject%d\n", i);
			if (cur_obj->id == sp)
			{
				ft_printf("\tsphere position:\t(%f, %f, %f)\n\tsphere diameter:\t%f\n", cur_obj->type.sp->pos->x, cur_obj->type.sp->pos->y, cur_obj->type.sp->pos->z, cur_obj->type.sp->dia);
			}
			else if (cur_obj->id == pl)
			{
				ft_printf("\tplane position:\t\t(%f, %f, %f)\n\tplane orientation:\t(%f, %f, %f)\n", cur_obj->type.pl->pos->x, cur_obj->type.pl->pos->y, cur_obj->type.pl->pos->z, cur_obj->type.pl->orien->x, cur_obj->type.pl->orien->y, cur_obj->type.pl->orien->z);
				
			}
			else if (cur_obj->id == sq)
			{
				ft_printf("\tsquare position:\t(%f, %f, %f)	\n\tsquare orientation:\t(%f, %f, %f)\n\tlength of side:\t\t%f\n", cur_obj->type.sq->pos->x, cur_obj->type.sq->pos->y, cur_obj->type.sq->pos->z, cur_obj->type.sq->orien->x, cur_obj->type.sq->orien->y, cur_obj->type.sq->orien->z, cur_obj->type.sq->side);

			}
			else if (cur_obj->id == cy)
			{
				ft_printf("\tcylinder position:\t(%f, %f, %f)\n\tcylinder orientation:\t(%f, %f, %f)\n\tdiameter:\t\t%f\n\theight:\t\t\t%f\n", cur_obj->type.cy->pos->x, cur_obj->type.cy->pos->y, cur_obj->type.cy->pos->z, cur_obj->type.cy->orien->x, cur_obj->type.cy->orien->y, cur_obj->type.cy->orien->z, cur_obj->type.cy->dia, cur_obj->type.cy->h);

			}
			else if (cur_obj->id == tr)
			{
				ft_printf("\ttriangle corner1:\t(%f, %f, %f)\n\ttriangle corner2:\t(%f, %f, %f)\n\ttriangle corner3:\t(%f, %f, %f)\n", cur_obj->type.tr->point1->x, cur_obj->type.tr->point1->y, cur_obj->type.tr->point1->z, cur_obj->type.tr->point2->x, cur_obj->type.tr->point2->y, cur_obj->type.tr->point2->z, cur_obj->type.tr->point3->x, cur_obj->type.tr->point3->y, cur_obj->type.tr->point3->z);

			}
			ft_printf("\tcolor:\t\t\t(%d, %d, %d)\n\n", cur_obj->color->r, cur_obj->color->g, cur_obj->color->b);

			cur_obj = cur_obj->next;
			i++;
		}
	}
}

// void free_scene(t_rt_scene *scene)
// {
	
// }

int main(int ac, char **av)
{
	t_rt_scene	*scene;
	t_mlx_data	*mlx_data;

	if (ac == 2 || (ac == 3 && ft_strncmp("--save", av[2], 7) == 0))
	{
		scene = get_scene(av[1]);
		mlx_data = init_mlx_data(scene);
		mlx_data->cam_info = gen_cam_data(mlx_data, mlx_data->scene->cam);
		if (ac == 2)
			manage_window(mlx_data);
		else
			save_img(mlx_data, av[1]);
		//TODO: destroy mlx_data, cam info and scene
		// free_scene(scene);
	}
	else
		error_exit_msg(C_MAIN_FEW_ARGUMENTS, E_MAIN_FEW_ARGUMENTS);
	return (0);
}
