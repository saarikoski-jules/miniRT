#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "quaternion.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//
#include <parse.h>

#define DIST 1 //choose: determine camera distance from grid
#define FOV_VERT 60 //choose: determine vertical fov
//choose: default rotation of camera, should be changeable.


// 	// ☺

//TODO: if two items are on the exact same 2D plane, which one displays? Right now the one mentioned earlier in the .rt file is displayed
//TODO: square is not visible if your camera and square orientation are the same
//TODO: cylinders break when seen more from the direction of the endcaps
//TODO: cylinder is rendered slightly wider than it's meant to
//TODO: what happens when any object is on top of me
//TODO: make sure any invalid arguments aren't accepted. Make sure --saved is the only extra thing that works



// t_vec *calculate_normal(t_vec *ray, t_vec *hit, t_obj *obj)
// {

// }

int cast(t_rt_scene *scene, t_vec *ray)
{
	t_obj *tmp;
	double d;
	double d_tmp;
	int	color;
	color = 0;
	d = 1.0/0.0; 
	d_tmp = -1.0;
	tmp = scene->obj;
	t_vec *n;
	n = gen_coord(0, 0, 0);
	if (tmp == NULL)
		return (0);
	while(tmp != NULL)
	{
		if (tmp != NULL)
		{
			if (tmp->id == sp)
			{

				// d_tmp = circle(scene, tmp->type.sp, ray, &n);
				d_tmp = circle(scene, scene->cam->pos, ray, tmp->type.sp, &n);
				// if (d_tmp == -10.0)
					// printf("aaa\n");

				//fix when sphere is on top of me
				// printf("sp\n");
			}
			else if (tmp->id == sq)
			{
				// d_tmp = square(scene, tmp->type.sq, ray, &n);
				d_tmp = square(scene, scene->cam->pos, ray, tmp->type.sq, &n);

				// printf("sq\n");
			}
			else if (tmp->id == tr)
			{
				// d_tmp = triangle(scene, tmp->type.tr, ray, &n);
				// printf("tr\n");
				d_tmp = triangle(scene, scene->cam->pos, ray, tmp->type.tr, &n);
			
			}
			else if (tmp->id == cy)
			{
				// t_vec *ray_start, t_vec *ray, t_cy *cy, t_vec **n
				// d_tmp = cylinder(scene, scene->cam->pos, ray, tmp->type.cy, &n);
				// printf("cy\n");
				d_tmp = cylinder(scene, scene->cam->pos, ray, tmp->type.cy, &n);

			}
			else if (tmp->id == pl)
			{
				// d_tmp = plane_intersect(scene, tmp->type.pl, ray, &n);
				// printf("pl\n");
				d_tmp = plane_intersect(scene, scene->cam->pos, ray, tmp->type.pl, &n);
			
			}
			if (d_tmp == -10.0)
			{
				// printf("-10\n");
				return (-10);
			}
		}

		if (d_tmp < d && d_tmp >= 0.0)
		{
			d = d_tmp;
			// if (d == -10) //if camera is inside an object, give me all black
			// {
				// return (-10);
			// }
			//get position from d, ray and camera position. Trace vector from point to all cameras and calculate combined color including ambiance
			t_color *rgb = calculate_final_color(scene, ray, tmp->color, d, tmp, n);  //fix this so it's only ran once per pixel??
			color = translate_color(rgb);
			// printf("dist: %f\n", d);
			// t_color *rgb = tmp->color;
		}
		tmp = tmp->next;
	}
	// printf("\n");
	return (color);
}

int remap_coord(t_rt_scene *scene, t_vec *pos, t_cam_info cam_data, t_qua *q)
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
	
	t_vec *vec = gen_coord(PixelScreenx, PixelScreeny, -1);
	t_vec *ray = orient_vector(q, vec);
	// t_vec *ray = gen_coord(PixelScreenx, PixelScreeny, pos->z); //Ray's direction ray
	
	
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

	// pos->x = 0;//
	// pos->y = 0;//

	t_vec *base = gen_coord(0, 0, -1);
	t_qua *q = determine_quaternion(scene->cam->orien, base);
	int color;

	// while (j <= 2)
	while (j <= scene->res->res_y)
	{
		// while (i <= 2)
		while (i <= scene->res->res_x)
		{
			color = remap_coord(scene, pos, cam_data, q);
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, color); //create image and put all at once instead.

			if (color == -10)
			{
				printf("inside obj\n");
				return;
			}
			if (i != scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 1;
		pos->x = inc_x /2;
		if (j != scene->res->res_y)
		{
			pos->y += inc_y;
		}
		j++;
	}
	printf("done\n");
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


	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "miniRT");
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