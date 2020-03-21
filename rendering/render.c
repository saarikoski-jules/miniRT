#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "libft.h"//

//ray casting: trace a ray until it hits an object
//ray tracing: trace a ray until it hits an object, which can generate new rays: reflection, refraction and shadow. These can be recursively calculated to determine the color of the pixel.
//shadow: trace rays toward each light. If there is an object between light and surface, light does not affect.

//Therefore: trace a ray up to an object and then call the same tracing function to lights, the combination of this should determine the color of the pixel

void trace_them_rays(t_rt_scene *scene)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int y;
	int color;

	y = 100;
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT);
	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "title");
	color = translate_color(scene->amb->color);
	ft_printf("%x\n", color);
	// while(y < 300)
	// {
	// 	mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
	// 	color += 1;
	// 	y++;
	// }
	mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
}
