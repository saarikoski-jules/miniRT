#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "libft.h"//

#define DIST 1 //choose: determine camera distance from grid
#define FOV_VERT 60 //choose: determine vertical fov
//choose: default rotation of camera, should be changeable.


//ray casting: trace a ray until it hits an object
//ray tracing: trace a ray until it hits an object, which can generate new rays: reflection, refraction and shadow. These can be recursively calculated to determine the color of the pixel.
//shadow: trace rays toward each light. If there is an object between light and surface, light does not affect.

//Therefore: trace a ray up to an object and then call the same tracing function to lights, the combination of this should determine the color of the pixel

//iterate through each pixel of the screen and shoot out a direct vector. 

// int is_perpendicular(t_vec *vec1, t_vec *vec2)
// {
// 	double res = (vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->x * vec2->x);
// 	ft_printf("res: %f\n", res);
// 	if (res == 0.0)
// 		return (1);
// 	return (0);
// }

// t_grid *get_grid_dimensions(t_rt_scene *scene, t_vec *dir)
// {
// 	t_vec	*mid;
// 	t_grid	*grid;

// 	mid = set_vec_len(dir, DIST);
// 	grid = (t_grid*)e_malloc(sizeof(t_grid));
// 	// ft_printf("mid: (%f, %f, %f)\n", mid->x, mid->y, mid->z);
// 	//THIS IS SO BROKEN PLS HALP



// 	double coord_x = mid->x + (scene->cam->fov / 2);
// 	double coord_y = mid->y + (FOV_VERT / 2);

// 	double res = (coord_x * dir->x) + (coord_y * dir->y);
// 	double final = res / dir->z;
// 	ft_printf("coord_x: %f, %f, coord_y: %f, %f\nres: %f\nfinal %f\n", coord_x, dir->x, coord_y, dir->y, res, final);


// 	// grid->up_left = gen_coord()

// 	// grid->up_left = gen_coord(mid->x - (scene->cam->fov / 2), mid->y + (FOV_VERT / 2), mid->z);
// 	// grid->up_right = gen_coord(mid->x + (scene->cam->fov / 2), mid->y + (FOV_VERT / 2), mid->z);
// 	// grid->down_left = gen_coord(mid->x - (scene->cam->fov / 2), mid->y - (FOV_VERT / 2), mid->z);
// 	// grid->down_right = gen_coord(mid->x + (scene->cam->fov / 2), mid->y - (FOV_VERT / 2), mid->z);

// }

// void iterate_pixels(t_rt_scene *scene, t_vec *dir, t_grid *grid)
// {
// 	t_vec *mov_x_dir;
// 	t_vec *mov_y_dir;
// 	double len_x;
// 	double len_y;
// 	t_vec *cur_pos;

// 	// ft_printf("fov: %d, res_x: %d\n", scene->cam->fov, scene->res->res_x);
// 	len_x = (double)scene->cam->fov / (double)scene->res->res_x;
// 	len_y = (double)FOV_VERT / (double)scene->res->res_y;
// 	mov_x_dir = determine_vector(grid->up_left, grid->up_right);
// 	mov_y_dir = determine_vector(grid->up_left, grid->down_left);
// 	cur_pos = gen_coord(grid->up_left->x, grid->up_left->y, grid->up_left->z);

// 	// ft_printf("fov: %d, res_x: %d\nlen_x: %f, len_y: %f\n", scene->cam->fov, scene->res->res_x ,len_x, len_y);
// 	// ft_printf("x (%f, %f, %f)\n", mov_x_dir->x, mov_x_dir->y, mov_x_dir->z);
// 	// ft_printf("y (%f, %f, %f)\n", mov_y_dir->x, mov_y_dir->y, mov_y_dir->z);
// 		// cur_pos->x = cur_pos->x + mov_x->x;
// 		// cur_pos->y = cur_pos->y + mov_x->y;
// 		// cur_pos->z = cur_pos->z + mov_x->z;
// 		// ft_printf("lup (%f, %f, %f)\n", cur_pos->x, cur_pos->y, cur_pos->z);

// 		// cur_pos->x = cur_pos->x + mov_x->x;
// 		// cur_pos->y = cur_pos->y + mov_x->y;
// 		// cur_pos->z = cur_pos->z + mov_x->z;
// 		// ft_printf("lup (%f, %f, %f)\n", cur_pos->x, cur_pos->y, cur_pos->z);

// 	// while (within_grid(cur_pos, grid))
// 	// {
// 	// 	cur_pos->x = cur_pos->x + mov_x->x;
// 	// 	cur_pos->y = cur_pos->y + mov_x->y;
// 	// 	cur_pos->z = cur_pos->z + mov_x->z;
// 	// 	// ft_printf("lup (%f, %f, %f)\n", cur_pos->x, cur_pos->y, cur_pos->z);
// 	// }
// 	// pixels are determined by resolution.
// 	// Divide grid into pixels by dividing it by resolution. increment by this amount
	
// }

// void trace(t_rt_scene *scene, t_vec *dir)
// {

// 	t_grid *grid;

// 	// is_perpendicular(dir, scene->cam->orien);

// 	grid = get_grid_dimensions(scene, dir);
// 	// ft_printf("up_left: (%f, %f, %f)\nup_right: (%f, %f, %f)\ndown_left: (%f, %f, %f)\ndown_left: (%f, %f, %f)\n", grid->up_left->x, grid->up_left->y, grid->up_left->z, grid->up_right->x, grid->up_right->y, grid->up_right->z, grid->down_left->x, grid->down_left->y, grid->down_left->z, grid->down_right->x, grid->down_right->y, grid->down_right->z);
// 	// iterate_pixels(scene, dir, grid);
	
// 	// ☺
// 	//corners: z + 1, y + FOV_VER / 2, x + FOV / 2
// 	//get position of current pixel
// 	//apply straight vector and check for collision.
// 	//how the hell do i determine where the dick my grid is?

// }

void get_ncd_coords(t_resolution *res)
{
	size_t i;
	size_t j;
	double inc_x;
	double inc_y;
	t_vec *pos;

	i = 1;
	j = 1;
	inc_x = 1.0/res->res_x;
	inc_y = 1.0/res->res_y;
	pos = (t_vec*)e_malloc(sizeof(t_vec));
	pos->z = 0;
	pos->x = inc_x / 2;
	pos->y = inc_y / 2;
	ft_printf("%f, %f\n", inc_x, inc_y);
	while (j <= res->res_y)
	{
		while (i <= res->res_x)
		{
			//get coord here.
			ft_printf("pix:\t(%d, %d)\tndc:\t(%f, %f, %f)\n", i, j, pos->x, pos->y,pos->z);
			if (i != res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 1;
		pos->x = inc_x /2;
		ft_printf("if %f < 1.0\n", pos->y + inc_y);
		if (j != res->res_y)
		{
			pos->y += inc_y;
		}
		j++;
	}
	// ft_printf("done\n");
}

void	trace(t_rt_scene *scene)
{
	get_ncd_coords(scene->res);
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
	// t_vec *dir = determine_vector(scene->cam->pos, scene->cam->orien);
	// ft_printf("vector: (%f, %f, %f)\n", dir->x, dir->y, dir->z);

	trace(scene);

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
	// mlx_loop(mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
}
