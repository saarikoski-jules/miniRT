/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/01 14:31:40 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"//
// #include "mlx.h"
#include "error.h"
#include "libft.h"
#include "rt.h"

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

// void trace_them_rays(t_rt_scene *scene)
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// 	void *img_ptr;
// 	int y;
// 	int color;

// 	y = 100;
// 	color = 0xff0000;
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT);
// 	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "title");
// 	while(y < 300)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
// 		color += 1;
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// 	img_ptr = mlx_new_image(mlx_ptr, 12, 12);
// }

int main(int ac, char **av)
{
	t_rt_scene	*scene;
	if (ac == 2)
		scene = get_scene(av[1]);
	else
		error_exit_msg(C_MAIN_FEW_ARGUMENTS, E_MAIN_FEW_ARGUMENTS);
	
	print_scene(scene);

	trace_them_rays(scene);
	return (0);
}
