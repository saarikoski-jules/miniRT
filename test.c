/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/14 19:51:03 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>//

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	
	mlx_ptr = mlx_init();
	// printf("%p\n", mlx_ptr);//
	win_ptr = mlx_new_window(mlx_ptr, 12, 12, "title");
	mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
	
	return (0);
}