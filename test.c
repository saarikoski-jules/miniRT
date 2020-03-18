/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko       #+#    #+#                */
/*   Updated: 2020/03/17 14:51:36 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "error.h"
#include "libft.h"
#include "rt.h"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_printf("Totally parsing %s rn\n", av[1]);
		get_input(av[1]);
	}
	else
		error_exit_msg(C_MAIN_FEW_ARGUMENTS, E_MAIN_FEW_ARGUMENTS);
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