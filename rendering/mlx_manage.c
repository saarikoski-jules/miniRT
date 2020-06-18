/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_manage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 11:13:01 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/18 17:26:54 by jsaariko      ########   odam.nl         */
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

void render_image(t_mlx_data *mlx_data, t_cam_info *cam_info)
{
	void		*image;
	int			endian; // 0 little endian, 1 big endian
	char		*img_addr;
	t_image_data *img_data;

	img_data = (t_image_data *)e_malloc(sizeof(t_image_data));
	image = mlx_new_image(mlx_data->mlx_ptr,
						mlx_data->scene->res->res_x,
						mlx_data->scene->res->res_y);
	if (image == NULL)
		error_exit_errno();
	img_addr = mlx_get_data_addr(image, &img_data->bpp, &img_data->size_line, &endian);
	img_data->image = &img_addr;
	ft_bzero(img_addr, img_data->size_line * mlx_data->scene->res->res_y);
	gen_image(cam_info, mlx_data->scene, img_data);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, image, 0, 0);
	
}

void manage_window(t_mlx_data *mlx_data)
{
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr,
										mlx_data->scene->res->res_x,
										mlx_data->scene->res->res_y, "miniRT");
	render_image(mlx_data, mlx_data->cam_info);
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
	if ((int)scene->res->res_x > screen_max_x) //TODO: save breaks with huge sizes
		scene->res->res_x = screen_max_x;
	if ((int)scene->res->res_y > screen_max_y)
		scene->res->res_y = screen_max_y;
	mlx_data->scene = scene;
	mlx_data->cam_amt = get_cam_amt(scene->cam);
	mlx_data->i = 0;
	return (mlx_data);
}