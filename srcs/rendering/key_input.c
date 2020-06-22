/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 12:35:40 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 15:29:38 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "xevents.h"
#include "manage_cameras.h"
#include "libft.h"//

int	close_program(void *mlx_data)
{
	(void)mlx_data;
	exit(0);
}

int	deal_key(int key, void *mlx_data)
{
	t_mlx_data **data;

	data = (t_mlx_data **)mlx_data;
	ft_printf("%d\n", key);
	if (key == KEYCODE_RIGHT || key == KEYCODE_LEFT)
	{
		free((*data)->cur_orien);
		(*data)->cur_orien = NULL;	
		(*data)->i = select_cam(key, *data);
	}
	else if (key == KEYCODE_UP)
		rotate_camera(key, data, (*data)->i);
	else if (key == KEYCODE_ESC)
		close_program(mlx_data);
	return (0);
}
