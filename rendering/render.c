#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "libft.h"//
#include <math.h>

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


int cast(t_rt_scene *scene, t_vec *vector)
{
	//calculate some_vec = origin of vector - center of circle
	//calculate some_vec_l = length (some_vec)
	//new_vec = pow(some_vec_l, 2)
	//sub = new_vec - (pow(r, 2))
	//dir_u = set_vec_len(vector, 1.0)
	//sub_from = pow(dir_u * some_vec, 2)
	//sub_from - sub


	// t_vec *tmp = substract_vectors(scene->cam->pos, scene->obj->type.sp->pos);
	// double tmp_len = det_len_vec(tmp);


//BETTER METHOD?

	// ft_printf("cam pos: (%f, %f, %f), sphere pos: (%f, %f, %f)\n", scene->cam->pos->x, scene->cam->pos->y, scene->cam->pos->z, scene->obj->type.sp->pos->x, scene->obj->type.sp->pos->y, scene->obj->type.sp->pos->z);
	// t_vec *c_o = substract_vectors(scene->obj->type.sp->pos, scene->cam->pos);
	// ft_printf("centre - origo: (%f, %f, %f)\n", c_o->x, c_o->y, c_o->z);
	// ft_printf("ray direction: (%f, %f, %f)\n", vector->x, vector->y, vector->z);
	// t_vec *dir_u = set_vec_len(vector, 1.0);
	// ft_printf("ray direction: (%f, %f, %f)\n", dir_u->x, dir_u->y, dir_u->z);
	// double c_o_dir_dot = get_dot_product(c_o, dir_u);
	// ft_printf("new c->o vector and direction dot product: %f\n", c_o_dir_dot);
	// double c_o_dot = get_dot_product(c_o, c_o);
	// double powco_dir = pow(c_o_dir_dot, 2);
	// double powco = pow(c_o_dot, 2);
	// ft_printf("%f - %f\n", powco, powco_dir);
	// double intersect = powco - powco_dir;
	// ft_printf("closest to circle center: %f, radius: %f\n", intersect, (scene->obj->type.sp->dia / 2.0));
	// ft_printf("c_o: (%f, %f, %f), co_dir: %f\n", c_o->x, c_o->y, c_o->z, c_o_dir);

	t_vec *L = substract_vectors(scene->obj->type.sp->pos, scene->cam->pos);
	// ft_printf("L: (%f, %f, %f)\n", L->x, L->y, L->z);
	double dot_L = get_dot_product(L, L);
	// ft_printf("dot product of L with itself: %f\n", dot_L);
	double r_pow = pow(scene->obj->type.sp->dia / 2.0, 2);
	// ft_printf("r: %f, r_pow: %f\n", scene->obj->type.sp->dia / 2.0, r_pow);
	t_vec *dir_u = set_vec_len(vector, 1.0);
	double dot_dir_L = get_dot_product(dir_u, L);
	// ft_printf("dit dot L: %f\n", dot_dir_L);

	double a = get_dot_product(dir_u, dir_u);
	// ft_printf("a: %f\n", a);
	double b = 2.0 * dot_dir_L;
	// ft_printf("b: %f\n", b);
	double c = dot_L - r_pow;
	// ft_printf("c: %f\n", c);

	double disc = pow(b, 2) - 4 * a * c;

	if (disc >= 0)
		return (1);
	else
		return (0);

	// ft_printf("pow b: %f, rest: %f, solved: %f\n", pow(b, 2),  4 * a * c, pow(b, 2) - 4 * a * c);

	// ft_printf("unit direction vector of ray: (%f, %f, %f)\ndir's dot product a: %f\n", dir_u->x, dir_u->y, dir_u->z, a);
	// double dot_centre_origo_dir = get_dot_product(L, dir_u);
	// ft_printf("dot product of L with dir_u: %f\n", dot_L);


	// if (intersect <= (scene->obj->type.sp->dia / 2.0))
		// return (1);
	// else
		// return (0);

}

//Translate remapped coords to real world space with transformation matrix


//get screen space
//I can shoot rays from here and return them so I can then draw pixels from the previous function
//I still need to account for direction
int remap_coord(t_rt_scene *scene, t_vec *pos)
{
	float aspect_ratio = scene->res->res_x / scene->res->res_y; //account for non square res
	float fov_y = tan(FOV_VERT / 2 * M_PI / 180);
	float fov_x = tan(scene->cam->fov / 2 * M_PI / 180);
	float PixelScreenx = ((pos->x * 2) - 1) * aspect_ratio * fov_x;
	float PixelScreeny = (1 - (pos->y * 2)) * fov_y;
	t_vec *vector = gen_coord(PixelScreenx, PixelScreeny, pos->z); //Ray's direction vector
	// ft_printf("vector: (%f, %f, %f), len: %f\n", vector->x, vector->y, vector->z, det_len_vec(vector));
	return (cast(scene, vector));
}

//get ndc space
void get_ndc_coords(t_rt_scene *scene, void *mlx_ptr, void *win_ptr)
{
	size_t i;
	size_t j;
	double inc_x;
	double inc_y;
	t_vec *pos;

	i = 1;
	j = 1;
	inc_x = 1.0/scene->res->res_x;
	inc_y = 1.0/scene->res->res_y;
	pos = (t_vec*)e_malloc(sizeof(t_vec));
	pos->z = -1; //we'll need to find the real number for this
	pos->x = inc_x / 2;
	pos->y = inc_y / 2;
	// ft_printf("%f, %f\n", inc_x, inc_y);
	// while (j <= 1)
	while (j <= scene->res->res_y)
	{
		// while (i <= 1)
		while (i <= scene->res->res_x)
		{
			//get coord here.
			// ft_printf("pix:\t(%d, %d)\tndc:\t(%f, %f, %f)\n", i, j, pos->x, pos->y,pos->z);
			// if (i == 250 && j == 250)
			// {
			if (remap_coord(scene, pos))
			{
				ft_printf("true\n");
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xff0000);
			}
			else
			{
				ft_printf("false\n");
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);
			}
			if (i != scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 1;
		pos->x = inc_x /2;
		// ft_printf("if %f < 1.0\n", pos->y + inc_y);
		if (j != scene->res->res_y)
		{
			pos->y += inc_y;
		}
		j++;
	}
	// ft_printf("done\n");
}

// void get_fisheye_ndc_coords(t_rt_scene *scene)
// {
// 	//view plane coords start from (-res_x/2, res_y/2). These can be translated then to the screen.
// 	//Then translate this to coords within (-1, 1) to (1, -1). These are fisheye ndc coords
// 	double x_start;
// 	double y_start;
// 	int i;
// 	int j;

// 	x_start = (scene->res->res_x/2.0)*-1;
// 	y_start = (scene->res->res_y/2.0);
// 	i = 0;
// 	j = 0;
// 	ft_printf("%f, %f\n", x_start, y_start);
// 	while ()
// 	{
		
// 	}
// }

void	trace(t_rt_scene *scene, void *mlx_ptr, void *win_ptr)
{
	get_ndc_coords(scene, mlx_ptr, win_ptr);
	// get_fisheye_ndc_coords(scene);
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


	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "title");
	trace(scene, mlx_ptr, win_ptr);

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