#include "render.h"
#include "rt.h"
#include "mlx.h"
#include "error.h"
#include "quaternion.h"
#include "libft.h"//
#include <math.h>
#include <stdio.h>//
#include <parse.h>
// #include "xevents.h"
// #include <X11/X.h> //TODO: should I use this, also <X11/keysymdef.h> for keycodes

#define DIST 1 //choose: determine camera distance from grid
#define FOV_VERT 60 //choose: determine vertical fov //TODO: calculate resolution ration and retermine vertical fov based on it?
//choose: default rotation of camera, should be changeable.



// 	// ☺

//TODO: fisheye lens for 180 fov
//TODO: if two items are on the exact same 2D plane, which one displays? Right now the one mentioned earlier in the .rt file is displayed
//TODO: square is not visible if your camera and square orientation are the same
//TODO: cylinders break when seen more from the direction of the endcaps
//TODO: cylinder is rendered slightly wider than it's meant to
//TODO: what happens when any object is on top of me
//TODO: make sure any invalid arguments aren't accepted. Make sure --saved is the only extra thing that works
//TODO: image flipped when looking behind. Is this bad?
//TODO: quaternions break when camera pointing directly into 0,0,-1 or 0,0,1.
//TODO: Bugfixes -> squares break with specific orientation (0,0,-1)
//TODO: is there a random segfault with file breaks_cy.rt

t_color *cast(t_rt_scene *scene, t_vec *ray, t_camera *cam)
{
	t_obj *tmp;
	double d;
	double d_tmp;
	unsigned int	color;
	color = 0;
	d = 1.0/0.0; 
	d_tmp = -1.0;
	tmp = scene->obj;
	t_vec *n;
	n = gen_coord(0, 0, 0);
	if (tmp == NULL)
		return (0);
	t_color *rgb;
	rgb = (t_color *)e_malloc(sizeof(t_color));
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
	while(tmp != NULL)
	{

		if (tmp != NULL)
		{
			if (tmp->id == sp)
			{

				d_tmp = sp_intersect(cam->pos, ray, tmp->type.sp);
			}
			else if (tmp->id == sq)
			{
				// if (get_dot_product(cam->orien, tmp->type.sq->orien) < 0)
					// ft_printf("breaks? %f\n", get_dot_product(cam->orien, tmp->type.sq->orien));
				d_tmp = sq_intersect(cam->pos, ray, tmp->type.sq);
			}
			else if (tmp->id == tr)
			{
				d_tmp = tr_intersect(cam->pos, ray, tmp->type.tr);
			}
			else if (tmp->id == cy)
			{
				d_tmp = cy_intersect(cam->pos, ray, tmp->type.cy);
				// if (d_tmp != 0.0 && d_tmp != NO_INTERSECT)
			}
			else if (tmp->id == pl)
			{
				d_tmp = pl_intersect(tmp->type.pl->orien, cam->pos, tmp->type.pl->pos, ray);
			
			}
			if (d_tmp == -10.0 || d_tmp == INSIDE_OBJ) //change
			{
				return (NULL);
			}
		}

		if (d_tmp < d && d_tmp > EPSILON)
		{
			// if (tmp->id == sq)
				// printf("sq: %f\n", d_tmp);
			// ft_printf("type: %d\nobj->color (%d, %d, %d)\n", tmp->id, tmp->color->r, tmp->color->g, tmp->color->b);
			
			// ft_printf("aa\n");
			d = d_tmp;
			rgb = calculate_final_color(scene, ray, tmp->color, d, tmp, n, cam);  //fix this so it's only ran once per pixel??
			// color = translate_color(rgb);
		}
		tmp = tmp->next;
	}
	return (rgb);
}

t_color *remap_coord(t_rt_scene *scene, t_vec *pos, t_cam_info *cam_data, t_vec *base, t_camera *cam)
{

	//currently I'm stretching image based on fov and aspect ratio difference. Do i want to??
	// double aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y; //account for non square res
	// double fov_a_ratio = (double)scene->cam->fov / (double)FOV_VERT; //maybe bad, please double check
	// ft_printf("aspect ratio: %f\n", aspect_ratio);
	// double fov_y = tan(FOV_VERT / 2 * M_PI / 180);
	// double fov_x = tan(scene->cam->fov / 2 * M_PI / 180);
	double PixelScreenx = ((pos->x * 2) - 1) * cam_data->aspect_ratio * cam_data->len_x;
	double PixelScreeny = (1 - (pos->y * 2)) * cam_data->len_y; //changes vertical fov slightly, so i can see a bit further/less depending on horizontal fov. Makes squishing slightly better, but I might want to use a different value or pillarbox instead. Quickie solution

// F = normalize(target - camera);   // lookAt
// R = normalize(cross(F, worldUp)); // sideaxis
// U = cross(R, F);                  // rotatedup


	t_vec *orien = set_vec_len(cam->orien, 1);
	if (det_len_vec(orien) != 1.0)
		ft_printf("will break\n");

	t_vec *cam_right;
	t_vec *world_up = gen_coord(0,1,0);
	if (orien->x == 0.0 && orien->z == 0.0) //cam orien must be normalized, otherwise this breaks
	{
		if (orien->y == -1.0)
			cam_right = gen_coord(1,0,0);
		else
			cam_right = gen_coord(-1,0,0);
	}
	else
		cam_right = get_cross_product(orien, world_up); //try when cam facing directly up
	// ft_printf("cam_right: %f, %f, %f\n", cam_right->x, cam_right->y, cam_right->z);
	t_vec *cam_right_u = set_vec_len(cam_right, 1.0);
	// t_vec *cam_right_u = cam_right;

	// ft_printf("cam_right_u:\t%f, %f, %f\n", cam_right_u->x, cam_right_u->y, cam_right_u->z);

	t_vec *cam_up = get_cross_product(cam_right_u, orien); //not possible these are the same?
	// t_vec *cam_up_u = set_vec_len(cam_up, 1);
	if (cam_right_u->x == orien->x && cam_right_u->y == orien->y && cam_right_u->z == orien->z)
		ft_printf("cross product fail in remap_coord\n");
	// ft_printf("cam_up:\t\t%f, %f, %f\n", cam_up->x, cam_up->y, cam_up->z);

	t_vec *trying_shit_x = gen_coord(PixelScreenx * cam_right_u->x, PixelScreenx * cam_right_u->y, PixelScreenx * cam_right_u->z);

	// ft_printf("pix_x:\t%f\n\t%f, %f, %f\n\n", PixelScreenx, trying_shit_x->x, trying_shit_x->y, trying_shit_x->z);
	
	t_vec *trying_shit_y = gen_coord(PixelScreeny * cam_up->x, PixelScreeny * cam_up->y, PixelScreeny * cam_up->z);

	// ft_printf("pix_y:\t%f\n\t%f, %f, %f\n\n", PixelScreeny, trying_shit_y->x, trying_shit_y->y, trying_shit_y->z);

	t_vec *trying_shit1 = add_vectors(trying_shit_x, trying_shit_y);
	t_vec *trying_shit2 = add_vectors(trying_shit1, orien);
	t_vec *ray_u = set_vec_len(trying_shit2, 1);
	return (cast(scene, ray_u, cam));
}

void	copy_pixel(t_color *color, int new, unsigned int rgb, size_t i, size_t j, void *mlx_ptr, char *img_addr, int screen_width, int pos)
{
	// ((unsigned int *)(img_addr))[(i + (500 * j))] = rgb;
	// ft_printf("i: %d, j: %d, pos %d\n", i, j, (i + screen_width * j));
	//500 is file pixels y
	// ft_memcpy(&img_addr[(4 * i + (4 * 500 * j))], &new, 3);
}

//get ndc space
void get_ndc_coords(t_cam_info *cam_data, t_camera *cam, t_resolution *res, t_vec *pos, t_rt_scene *scene, void *mlx_ptr, void *win_ptr, t_vec *base, double inc_x, double inc_y)
{
	size_t i;
	size_t j;
	// int color;
	// unsigned int color;
	int color;
	t_color *rgb;
	void *image;

	//i could save images to a list in case of multiple cameras
	i = 0;
	j = 0;
	int k;
	k = 0;
	image = mlx_new_image(mlx_ptr, scene->res->res_x, scene->res->res_y);
	if (image == NULL)
		error_exit_errno();
	int bpp;
	int size_line;
	int endian; // 0 little endian, 1 big endian
	// unsigned int *img_byte;			//img ptr, 
	char *img_addr = mlx_get_data_addr(image, &bpp, &size_line, &endian);//have to use this for img to work
	// unsigned int *img_addr_uint = (unsigned int *)img_addr;
	// img_byte = (unsigned int *)image
	int img_size =  size_line * scene->res->res_y;

	ft_bzero(img_addr, img_size); //make sure img is initialized to zero
	// ft_printf("%d, %d, %d", bpp, size_line, endian);
	int new;
	int pix_pos;
	while (j < scene->res->res_y)
	{
		while (i < scene->res->res_x)
		{
			ft_printf("inc x: %f, y: %f\nres x: %d, y: %d\n\n", pos->x, pos->y, i, j);
			// ft_printf("mlx_shit cam: %p\n", cam);
			rgb = remap_coord(scene, pos, cam_data, base, cam);
			color = translate_color(rgb);
			// ft_printf("i * j: %d, i: %d, j: %d\n", i * j, i, j);
			// if (pix_pos > img_size)

				// ft_printf("pix_pos %d\n", pix_pos);
			// unsigned int rgb = translate_color(color);
			pix_pos = (j * size_line + i * (bpp / 8)); //should this be zero indexed?
			// ft_printf("pix_pos: %d, img_size %d\n", pix_pos, img_size);
			// ft_printf("pix_pos: %d\n", pix_pos);
			ft_memcpy(img_addr + pix_pos, &color, 3);
			if (color == INSIDE_OBJ)
			{
				return; //maybe not? just paste all black?
			}
			if (i < scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 0;
			pos->x = inc_x /2;
		if (j < scene->res->res_y)//TODO: Make sure all of these are correct
		{
			pos->y += inc_y;
		}
		j++;

	}
	ft_printf("incrememnt max values: %f, %f\n", pos->y, pos->x);
	ft_printf("here\n");
	ft_printf("img_ptr %p\n", image);
	// if (fd == -1)
	mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
	ft_printf("size_line: %d\n", size_line);
	ft_printf("final pix_pos: %d\n", pix_pos);
	// else
		// write(fd, image, res->res_x * res->res_y); //check for bad return value
	printf("done\n");
}

void append_color(int color, int i, int j, int size_line, int bpp, int endian, char *image, int k)
{
	// int pix_pos = (j * size_line + i * (bpp / 8)); //should this be zero indexed?
}



void get_ndc_coords_save(t_cam_info *cam_data, t_camera *cam, t_resolution *res, t_vec *pos, t_rt_scene *scene, void *mlx_ptr, void *win_ptr, t_vec *base, double inc_x, double inc_y, int fd) // if write fails, exit instead of bad return
{
	size_t i;
	size_t j;
	t_color *color;

	i = 0;
	j = 0;
	int k;
	k = 0;
	char *image;
	int bpp = 24;//idk
	int size_line = scene->res->res_x * (bpp / 8);//idk
		while(size_line % 4 != 0)
			size_line++;
	int endian = 0; // 0 little endian, 1 big endian, idk
	int amt_pixels = scene->res->res_y * scene->res->res_x; 
	int img_size = size_line * scene->res->res_y; //amt_pixels * 3 bytes + scene->res->res_y * scene->res->res_x 
	// ft_printf("sizeline: %d\n", size_line);
	image = (char *)e_malloc(img_size);
	// ft_printf("img_size: %d\n", img_size);
	ft_bzero(image, img_size); //make sure img is initialized to zero
	int new;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int pix_pos;
	int black = 0;
	int white = 255;
	int r_bit;
	int g_bit;
	int b_bit;

	int rgb;

	while (j < scene->res->res_y)
	{
		k = size_line * j;
		if (j < 3)
			ft_printf("k1 : %d\n", k);
		while (i < scene->res->res_x)
		{
			// ft_printf("aa\n");
			color = remap_coord(scene, pos, cam_data, base, cam); //TODO: make sure color value is good when no intersections
			if (color == NULL)
			{
				//just zeroes
			}
			r = color->r;
			g = color->g;
			b = color->b;
			// bgr = translate_color(color);
			// ft_printf("k: %d\n", k);
				ft_memcpy(image + k, &b, 1);
				ft_memcpy(image + k + 1, &g, 1);
				ft_memcpy(image + k + 2, &r, 1);	
			k += 3;
			// int pix_pos = (j * size_line + i * (bpp / 8)); //should this be zero indexed?
			// ft_memcpy(img_addr + pix_pos, &color, 3);
			// if (color == NULL)
			// {
				// return; //maybe not? just paste all black? //already pasting all black (bzero)
			// }
			if (i < scene->res->res_x)
			{
				pos->x += inc_x;
			}
			i++;
		}
		i = 0;
			pos->x = inc_x / 2;
		if (j < scene->res->res_y)
		{
			pos->y += inc_y;
		}
		j++;
		// k = size_line * (j - 1);
		if (j < 3)
			ft_printf("k2 : %d\n", k);
		// while ((k) % 4 != 0)
		// {
			// ft_printf("??\n");
			// k++;
		// }

	}
	ft_printf("here\n");
	ft_printf("img_ptr %p\n", image);
	ft_printf("k: %d\n", k);
	// if (fd == -1)
	// mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
	// else
	// write(fd, "AAAAAAAAA", 9); //check for bad return value
	write(fd, image, img_size); //check for bad return value
	// ft_printf("'%s'\n", image);
	printf("done\n");
}



void	trace(t_mlx_data *mlx_data, t_camera *cam, int fd) //init cam data
{
	double inc_x;
	double inc_y;
	t_vec *pos;
	t_cam_info *cam_data;
	// t_camera *cam_cur;

	// cam_cur = scene->cam;
		cam_data = (t_cam_info *)e_malloc(sizeof(t_cam_info));
		cam_data->aspect_ratio = (double)mlx_data->scene->res->res_x / (double)mlx_data->scene->res->res_y;
		cam_data->fov_ratio = (double)cam->fov / (double)FOV_VERT; //changing maybe
		cam_data->len_x = tan(cam->fov / 2 * M_PI / 180);
		cam_data->len_y = tan(FOV_VERT / 2 * M_PI / 180); //TODO: calculate new FOV_VERT
		inc_x = 1.0/mlx_data->scene->res->res_x;
		inc_y = 1.0/mlx_data->scene->res->res_y;
		pos = (t_vec*)e_malloc(sizeof(t_vec));
		pos->y = inc_y / 2;
		t_vec *base;
		base = gen_coord(0, 0, -1);
		pos->x = inc_x / 2;
		pos->z = -1;
	ft_printf("cam: %p\n", cam);
		if (fd == -1)
			get_ndc_coords(cam_data, cam, mlx_data->scene->res, pos, mlx_data->scene, mlx_data->mlx_ptr, mlx_data->win_ptr, base, inc_x, inc_y);
		else
			get_ndc_coords_save(cam_data, cam, mlx_data->scene->res, pos, mlx_data->scene, mlx_data->mlx_ptr, mlx_data->win_ptr, base, inc_x, inc_y, fd); //if fails, exit??
}
