/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 12:35:40 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/18 17:24:23 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"//
#include "rt.h"//
#include "xevents.h"//
#include <stdlib.h>//
#include "libft.h"//
#include "manage_cameras.h"//

//TODO: make sure window doesnt break when moving, resizing, closing or exposing from behind other window

int close_program(void *mlx_data)
{
	(void)mlx_data;
	exit(0);//exit success??
}

int	deal_key(int key, void *mlx_data)
{
	t_mlx_data **data;

	data = (t_mlx_data **)mlx_data;
	if (key == KEYCODE_RIGHT || key == KEYCODE_LEFT)
		(*data)->i = select_cam(key, *data); //TODO if return -1, exit, or see if this isnt possible
	else if (key == KEYCODE_ESC)
		close_program(mlx_data);
	else
		ft_printf("invalid key\n");//
	return (0);
}

