/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 16:19:59 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "render.h"

int	main(int ac, char **av)
{
	t_rt_scene	*scene;
	t_mlx_data	*mlx_data;
	t_cam_info	*cam_data;

	if (ac == 2 || (ac == 3 && ft_strncmp("--save", av[2], 7) == 0))
	{
		scene = get_scene(av[1]);
		cam_data = gen_cam_data(scene, scene->cam);
		if (ac == 2)
		{
			mlx_data = init_mlx_data(scene);
			mlx_data->cam_info = cam_data;
			manage_window(mlx_data);
		}
		else
		{
			save_img(scene, cam_data, av[1]);
		}
	}
	else
		error_exit_msg(C_MAIN_FEW_ARGUMENTS, E_MAIN_FEW_ARGUMENTS);
	return (0);
}
