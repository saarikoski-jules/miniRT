#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//

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


double circle(t_rt_scene *scene, t_obj *sp, t_vec *ray)
{
	t_vec *L = substract_vectors(scene->cam->pos, sp->type.sp->pos);
	double dot_L = get_dot_product(L, L);
	double r_pow = pow(sp->type.sp->dia / 2.0, 2);
	
	// ft_printf("circle dia: %f, circle pos: (%f, %f, %f)\n", sp->type.sp->dia, sp->type.sp->pos->x, sp->type.sp->pos->y, sp->type.sp->pos->z);

	// ft_printf("ray: (%f, %f, %f)\n", ray->x, ray->y, ray->z);
	t_vec *dir_u = set_vec_len(ray, 1.0);
	// ft_printf("ray_unit: (%f, %f, %f)\n", dir_u->x, dir_u->y, dir_u->z);
	double dot_dir_L = get_dot_product(dir_u, L);
	// ft_printf("DOT PRODUCT FOR A: \n");
	// double a = get_dot_product(dir_u, dir_u);
	double a = 1.0;
	// ft_printf("\n\n");
	double b = 2.0 * dot_dir_L;
	// ft_printf("%f\n", b);
	double c = dot_L - r_pow;
	// ft_printf("a: %f, b: %f, c: %f\n", a, b, c);
	// ft_printf("%f\n", dir_u);
	double disc = pow(b, 2) - 4 * a * c;
	// ft_printf("%f - 4 *%f * %f = %f\n", pow(b, 2), a, c, disc);
	// ft_printf("a: %f\n", a);
	// ft_printf("disc: %f\n", disc);
	// ft_printf("%f\n", disc);
	if (disc < 0)
		return (-1.0);
	//if intersections are found, get distance from camera

	if (disc > 0)
	{
		// ft_printf("b: %f\n", b);
		// ft_printf("a: %f, b: %f, c: %f\n", a, b, c);
		//calculate (-b - disc) / 2a and (-b + disk) / 2a
		// printf("-b: %f\n", -1 * b);
		// printf("disc: %f, sqrt(disc): %f\n", disc, sqrt(disc));
		double d1 = (((-1 * b) - sqrt(disc)) / 2);
		double d2 = (((-1 * b) + sqrt(disc)) / 2);
		if (d1 < d2)
			return (d1);
		else
			return (d2);
		// if (d1 > d2)
			// printf("d1: %f\n", d1);
		// else
			// printf("d2: %f\n", d2);
	}
	else if (disc == 0)
	{
		double d = (-1 * b) / (2 * a);
		return (d);
	}
	return (0);
	// if (disc >= 0 && b >= 0)
	// 	return (translate_color(sp->color));
	// else
	// 	return (0);
}

double plane(t_rt_scene *scene, t_obj *pl, t_vec *ray)
{
	double d;
	//p0 = pl->type.pl->pos;
	//l0 = scene->cam->pos;
	//n = pl->type.pl->orien;
	//l = ray

	// t_vec *n = substract_vectors(pl->type.pl->pos, pl->type.pl->orien);
	double ln = get_dot_product(ray, pl->type.pl->pos);
	if (ln == 0.0)
		return (-1);
	// ft_printf("ray: (%f, %f, %f)\n", ray->x, ray->y, ray->z);
	// ft_printf("ln: %f\n", ln);
	t_vec *cam_pl = substract_vectors(pl->type.pl->pos, scene->cam->pos);
	// ft_printf("cam_pl: (%f, %f, %f)\n", cam_pl->x, cam_pl->y, cam_pl->z);
	double cam_pl_n = get_dot_product(cam_pl, pl->type.pl->orien);
	// if (p0 - l0)n == 0 (cam_pl_n == 0)camera is inside the object
	// ft_printf("%f, %f\n", cam_pl_n, ln);
	double tmp = cam_pl_n / ln;
	t_vec *halp = gen_coord(ray->x * tmp, ray->y * tmp, ray->z *tmp);
	// ft_printf("halp: (%f, %f, %f)\n", halp->x, halp->y, halp->z);
	t_vec *sub = add_vectors(scene->cam->pos, halp);
	d = det_len_vec(sub);
	return (d);
	// ft_printf("d: %f\n", d)

	// ft_printf("d: %f\n", d);


	return (-1);
}

int cast(t_rt_scene *scene, t_vec *ray)
{
	//iterate objects

	t_obj *tmp;
	double d;
	double d_tmp;
	int	color;

	color = 0;
	d = -1.0;
	tmp = scene->obj;
	if (tmp == NULL)
		return (0);
	while(tmp != NULL)
	{
		// ft_printf("goooo\n");
		//save the closest value to the camera and return that
		if (tmp != NULL)
		{
			// ft_printf("go\n");
			if (tmp->id == sp)
			{
				// ft_printf("circle\n");
				// ft_printf("%d\n", tmp);

				// ft_printf("\tsphere position:\t(%f, %f, %f)\n\tsphere diameter:\t%f\n", tmp->type.sp->pos->x, tmp->type.sp->pos->y, tmp->type.sp->pos->z, tmp->type.sp->dia);

					// ft_printf("circle dia: %f, circle pos: (%f, %f, %f) color: (%d, %d, %d)\n", tmp->type.sp->dia, tmp->type.sp->pos->x, tmp->type.sp->pos->y, tmp->type.sp->pos->z, tmp->color->r, tmp->color->g, tmp->color->b);
				d_tmp = circle(scene, tmp, ray);
				// ft_printf("d temp: %f, circle\n", d_tmp);
				// printf("distance: %f\n", d_tmp);
				if (d_tmp > d && d_tmp > 0.0)
				{
					d = d_tmp;
					// if (d != -1.0)
						// ft_printf("%f\n", d);
					color = translate_color(tmp->color);
					// ft_printf("assign color circle %x\n", color);
					// ft_printf("circle, color %x\n", color);
				}
			//fix when sphere is on top of me
			}
			else if (tmp->id == pl)
			{
				d_tmp = plane(scene, tmp, ray);
				// ft_printf("d temp: %f, plane\n", d_tmp);
				if (d_tmp > d && d_tmp > 0.0)
				{
					// ft_printf("assign color plane\n");
					d = d_tmp;
					color = translate_color(tmp->color);
					// ft_printf("plane, color %x\n", color);
				}
			// ft_printf("plane?\n");
			}
		}
		// printf("%p\n", tmp->next);
		tmp = tmp->next;
	}
	// ft_printf("\nwinning color: %x\n\n\n", color);
	return (color);


	// ft_printf("pow b: %f, rest: %f, solved: %f\n", pow(b, 2),  4 * a * c, pow(b, 2) - 4 * a * c);

	// ft_printf("unit direction ray of ray: (%f, %f, %f)\ndir's dot product a: %f\n", dir_u->x, dir_u->y, dir_u->z, a);
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
int remap_coord(t_rt_scene *scene, t_vec *pos, t_cam_info cam_data)
{

	//currently I'm stretching image based on fov and aspect ratio difference. Do i want to??
	// double aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y; //account for non square res
	// double fov_a_ratio = (double)scene->cam->fov / (double)FOV_VERT; //maybe bad, please double check
	// ft_printf("aspect ratio: %f\n", aspect_ratio);
	// double fov_y = tan(FOV_VERT / 2 * M_PI / 180);
	// double fov_x = tan(scene->cam->fov / 2 * M_PI / 180);
	double PixelScreenx = ((pos->x * 2) - 1) * cam_data.aspect_ratio * cam_data.len_x;
	double PixelScreeny = (1 - (pos->y * 2)) * cam_data.len_y * cam_data.fov_ratio; //changes vertical fov slightly, so i can see a bit further/less depending on horizontal fov. Makes squishing slightly better, but I might want to use a different value or pillarbox instead. Quickie solution
	// ft_printf("ray: (%f, %f, %f), pos: (%f, %f, %f) fov_a_ratio: %f\n", PixelScreenx, PixelScreeny, pos->z, pos->x, pos->y, pos->z, fov_a_ratio);
	t_vec *ray = gen_coord(PixelScreenx, PixelScreeny, pos->z); //Ray's direction ray
	// ft_printf("ray: (%f, %f, %f), len: %f\n", ray->x, ray->y, ray->z, det_len_vec(ray));
	return (cast(scene, ray));
}

//get ndc space
void get_ndc_coords(t_rt_scene *scene, void *mlx_ptr, void *win_ptr)
{
	size_t i;
	size_t j;
	double inc_x;
	double inc_y;
	t_vec *pos;
	t_cam_info cam_data;

	cam_data.aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y;
	cam_data.fov_ratio = (double)scene->cam->fov / (double)FOV_VERT; //changing maybe
	cam_data.len_x = tan(scene->cam->fov / 2 * M_PI / 180);
	cam_data.len_y = tan(FOV_VERT / 2 * M_PI / 180);

	i = 1;
	j = 1;
	inc_x = 1.0/scene->res->res_x;
	inc_y = 1.0/scene->res->res_y;
	pos = (t_vec*)e_malloc(sizeof(t_vec));
	pos->z = -1; //we'll need to find the real number for this
	pos->x = inc_x / 2;
	pos->y = inc_y / 2;
	// ft_printf("%f, %f\n", inc_x, inc_y);

	// while (j <= 2)
	while (j <= scene->res->res_y)
	{
		// while (i <= 2)
		while (i <= scene->res->res_x)
		{
			//get coord here.
			// ft_printf("pix:\t(%d, %d)\tndc:\t(%f, %f, %f)\n", i, j, pos->x, pos->y,pos->z);
			// if (i == 250 && j == 250)
			// {
			
			// if (remap_coord(scene, pos))
			// {
				// ft_printf("true\n");
				// if (i == 250 && j == 250)
					mlx_pixel_put(mlx_ptr, win_ptr, i, j, remap_coord(scene, pos, cam_data));
			// }
			// else
			// {
				// ft_printf("false\n");
				// mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);
			// }
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