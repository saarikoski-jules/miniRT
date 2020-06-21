/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 12:35:40 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 17:41:24 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "xevents.h"
#include "manage_cameras.h"

int close_program(void *mlx_data)
{
	(void)mlx_data;
	exit(0);
}

int	deal_key(int key, void *mlx_data)
{
	t_mlx_data **data;

	data = (t_mlx_data **)mlx_data;
	if (key == KEYCODE_RIGHT || key == KEYCODE_LEFT)
		(*data)->i = select_cam(key, *data);
	else if (key == KEYCODE_ESC)
		close_program(mlx_data);
	return (0);
}
