/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/15 13:32:38 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"

int main(int amt, char **args)
{
	if (amt == 2)
	{
		
	}
	else
	{
		ft_printf("ERROR\noops, bad args\n");
	}
	
	return (0);
}

// void trace_them_rays()
// {
	// void *mlx_ptr;
	// void *win_ptr;
	// void *img_ptr;
	// int y;
	// int color;

	// y = 100;
	// color = 0x000000;
	// mlx_ptr = mlx_init();
	// ft_printf("%p\n", mlx_ptr);
	// win_ptr = mlx_new_window(mlx_ptr, 500, 500, "title");
	// while(y < 300)
	// {
		// mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
		// color += 1;
		// y++;
	// }
	// mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
	
// }