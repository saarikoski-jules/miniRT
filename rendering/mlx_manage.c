/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_manage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 11:13:01 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/13 13:15:50 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "xevents.h"
#include "mlx.h"
#include "rt.h"//
#include "render.h"//
#include <stdlib.h>//
#include "libft.h"//
#include "error.h"//
#include "key_functions.h"//
#include "manage_cameras.h"//


void manage_window(t_mlx_data *mlx_data)
{
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, mlx_data->scene->res->res_x, mlx_data->scene->res->res_y, "miniRT"); //dont want this is --save
	trace(mlx_data, mlx_data->scene->cam, -1);
	mlx_key_hook(mlx_data->win_ptr, deal_key, &mlx_data);
	mlx_hook(mlx_data->win_ptr, DESTROY_NOTIFY, SUBSTRUCTURE_NOTIFY_MASK, close_program, &mlx_data);
	mlx_loop(mlx_data->mlx_ptr);
}

t_mlx_data *init_mlx_data(t_rt_scene *scene)
{
	t_mlx_data	*mlx_data;
	int			screen_max_x;
	int			screen_max_y;

	mlx_data = (t_mlx_data *)e_malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT); //TODO: check if error msg is alright
	mlx_get_screen_size(mlx_data->mlx_ptr, &screen_max_x, &screen_max_y);
	if (scene->res->res_x > screen_max_x) //TODO: save breaks with huge sizes
		scene->res->res_x = screen_max_x;
	if (scene->res->res_y > screen_max_y)
		scene->res->res_y = screen_max_y;
	mlx_data->scene = scene;
	mlx_data->cam_amt = get_cam_amt(scene->cam);
	mlx_data->i = 0;
	return (mlx_data);
}