#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "libft.h"//

#define DIST 1
#define FOV_VERT 100

//ray casting: trace a ray until it hits an object
//ray tracing: trace a ray until it hits an object, which can generate new rays: reflection, refraction and shadow. These can be recursively calculated to determine the color of the pixel.
//shadow: trace rays toward each light. If there is an object between light and surface, light does not affect.

//Therefore: trace a ray up to an object and then call the same tracing function to lights, the combination of this should determine the color of the pixel

//iterate through each pixel of the screen and shoot out a direct vector. 

t_grid *get_grid_dimensions(t_rt_scene *scene, t_vec *dir)
{
	t_vec	*mid;
	t_grid	*grid;

	mid = set_vec_len(dir, DIST);
	grid = (t_grid*)e_malloc(sizeof(t_grid));
	ft_printf("mid: (%f, %f, %f)\n", mid->x, mid->y, mid->z);
	grid->up_left = gen_coord(mid->x - (scene->cam->fov / 2), mid->y + (FOV_VERT / 2), mid->z);
	grid->up_right = gen_coord(mid->x + (scene->cam->fov / 2), mid->y + (FOV_VERT / 2), mid->z);
	grid->down_left = gen_coord(mid->x - (scene->cam->fov / 2), mid->y - (FOV_VERT / 2), mid->z);
	grid->down_right = gen_coord(mid->x + (scene->cam->fov / 2), mid->y - (FOV_VERT / 2), mid->z);

}

void iterate_pixels(t_rt_scene *scene, t_vec *dir, t_grid *grid)
{
	// pixels are determined by resolution.
	// Divide grid into pixels by dividing it by resolution. increment by this amount


}

void trace(t_rt_scene *scene, t_vec *dir)
{
	t_grid *grid;

	grid = get_grid_dimensions(scene, dir);
	ft_printf("up_left: (%f, %f, %f)\nup_right: (%f, %f, %f)\ndown_left: (%f, %f, %f)\ndown_left: (%f, %f, %f)\n", grid->up_left->x, grid->up_left->y, grid->up_left->z, grid->up_right->x, grid->up_right->y, grid->up_right->z, grid->down_left->x, grid->down_left->y, grid->down_left->z, grid->down_right->x, grid->down_right->y, grid->down_right->z);
	iterate_pixels(scene, dir, grid);
	
	// ☺
	//corners: z + 1, y + FOV_VER / 2, x + FOV / 2
	//get position of current pixel
	//apply straight vector and check for collision.
	//how the hell do i determine where the dick my grid is?

}

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
	//direction vector for a straight vector for collision checking.
	t_vec *dir = determine_vector(scene->cam->pos, scene->cam->orien);
	// ft_printf("vector: (%f, %f, %f)\n", dir->x, dir->y, dir->z);

	trace(scene, dir);

	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "title");

	//get straight vector
	//get position of current pixel
	//apply straight vector with current pixel to check for collision

	
	

	// color = translate_color(scene->amb->color);
	// ft_printf("%x\n", color);
	// while(y < 300)
	// {
	// 	mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
	// 	color += 1;
	// 	y++;
	// }
	mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
}
