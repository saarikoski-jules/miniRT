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

int cast(t_rt_scene *scene, t_vec *ray, t_camera *cam)
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
			if (d_tmp == -10.0 || d_tmp == INSIDE_OBJ)
			{
				return (INSIDE_OBJ);
			}
		}

		if (d_tmp < d && d_tmp > EPSILON)
		{
			// if (tmp->id == sq)
				// printf("sq: %f\n", d_tmp);
			// ft_printf("type: %d\nobj->color (%d, %d, %d)\n", tmp->id, tmp->color->r, tmp->color->g, tmp->color->b);
			
			d = d_tmp;
			t_color *rgb = calculate_final_color(scene, ray, tmp->color, d, tmp, n, cam);  //fix this so it's only ran once per pixel??
			color = translate_color(rgb);
		}
		tmp = tmp->next;
	}
	return (color);
}

int remap_coord(t_rt_scene *scene, t_vec *pos, t_cam_info *cam_data, t_qua *q, t_vec *base, t_camera *cam)
{

	//currently I'm stretching image based on fov and aspect ratio difference. Do i want to??
	// double aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y; //account for non square res
	// double fov_a_ratio = (double)scene->cam->fov / (double)FOV_VERT; //maybe bad, please double check
	// ft_printf("aspect ratio: %f\n", aspect_ratio);
	// double fov_y = tan(FOV_VERT / 2 * M_PI / 180);
	// double fov_x = tan(scene->cam->fov / 2 * M_PI / 180);
	double PixelScreenx = ((pos->x * 2) - 1) * cam_data->aspect_ratio * cam_data->len_x;
	double PixelScreeny = (1 - (pos->y * 2)) * cam_data->len_y; //changes vertical fov slightly, so i can see a bit further/less depending on horizontal fov. Makes squishing slightly better, but I might want to use a different value or pillarbox instead. Quickie solution
	// ft_printf("ray: (%f, %f, %f), pos: (%f, %f, %f) fov_a_ratio: %f\n", PixelScreenx, PixelScreeny, pos->z, pos->x, pos->y, pos->z, fov_a_ratio);
	
	t_vec *vec = gen_coord(PixelScreenx, PixelScreeny, base->z);
	// ft_printf("%f, %f, %f\n", vec->x, vec->y, vec->z);
	// if (vec->x == 1 && vec->y == 0 && vec->z == 0)
		// ft_printf("aa\n");
	// ft_printf("vec: (%f, %f, %f)\n", vec->x, vec->y, vec->z);

	t_vec *ray = orient_vector(q, vec);
	t_vec *ray_aa = orient_vector_attempt2(q, vec);
	// ft_printf("ray: (%f, %f, %f)\n", ray->x, ray->y, ray->z);
	// t_vec *ray_u = set_vec_len(ray, 1);
	t_vec *ray_u = set_vec_len(ray, 1);
	// ft_printf("ray: (%f, %f, %f)\n\n", ray_u->x, ray_u->y, ray_u->z);
	// t_vec *ray = gen_coord(PixelScreenx, PixelScreeny, pos->z); //Ray's direction ray
	
	
	// ft_printf("ray: (%f, %f, %f), len: %f\n", ray->x, ray->y, ray->z, det_len_vec(ray));
	
	return (cast(scene, ray_u, cam));
}


//get ndc space
void get_ndc_coords(t_cam_info *cam_data, t_camera *cam, t_resolution *res, t_qua *q, t_vec *pos, t_rt_scene *scene, void *mlx_ptr, void *win_ptr, t_vec *base, double inc_x, double inc_y)
{
	size_t i;
	size_t j;
	int color;


	i = 1;
	j = 1;
	// while (j <= 2)
			// ft_printf("pos %f\n", pos->x);
	while (j <= scene->res->res_y)
	{
		// if (pos->x < 0)
			// ft_printf("pos %f\n", pos->x);
		// while (i <= 2)
		while (i <= scene->res->res_x)
		{
			// if (pos->x < 0)
				// ft_printf("pos->x: %f\n", pos->x);
			// if (i == 270 && j == 330)
			// {
				// color = 0xffffff;
				// if (j < 400 && j > 300 && i < 150 && i > 100)
					color = remap_coord(scene, pos, cam_data, q, base, cam);
				// else
					// color = 200;
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, color); //create image and put all at once instead.
			// }
			if (color == INSIDE_OBJ)
			{
				// printf("inside obj\n");
				return;
			}
			if (i != scene->res->res_x)
			{
				// ft_printf("inc_x: %f\n", inc_x);
				pos->x += inc_x;
				// ft_printf("pos->x: %f, i: %d\n", pos->x, i);
			}
			i++;
		}
		i = 1;
		if (cam->orien->z > 0)
		{
			pos->x = 1 + (inc_x / 2);
		}
		else
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



void	trace(t_rt_scene *scene, void *mlx_ptr, void *win_ptr, t_camera *cam)
{
	double inc_x;
	double inc_y;
	t_vec *pos;
	t_cam_info *cam_data;
	// t_camera *cam_cur;

	
	// cam_cur = scene->cam;
		cam_data = (t_cam_info *)e_malloc(sizeof(t_cam_info));
		cam_data->aspect_ratio = (double)scene->res->res_x / (double)scene->res->res_y;
		cam_data->fov_ratio = (double)cam->fov / (double)FOV_VERT; //changing maybe
		cam_data->len_x = tan(cam->fov / 2 * M_PI / 180);
		cam_data->len_y = tan(FOV_VERT / 2 * M_PI / 180);
		inc_x = 1.0/scene->res->res_x;
		inc_y = 1.0/scene->res->res_y;
		pos = (t_vec*)e_malloc(sizeof(t_vec));
		// if (cam->orien->z > 0)
			// pos->z = 1; //we'll need to find the real number for this
		// else
			// pos->z = -1;
		pos->y = inc_y / 2;

		// pos->x = 0;//
		// pos->y = 0;//
		t_vec *base;
		if (cam->orien->z > 0)
		{
			base = gen_coord(0, 0, 1);
			inc_x = inc_x * (-1);
			pos->x = 1 + (inc_x / 2);
			pos->z = 1;
		}
		else
		{
			base = gen_coord(0, 0, -1); 
			pos->x = inc_x / 2;
			pos->z = -1;
		}
		t_qua *q = determine_quaternion(cam->orien, base);
		t_qua *q_matrix = determine_quaternion_matrix(cam->orien, base);
		ft_printf("q:\t%f (%f, %f, %f)\n", q->w, q->vector->x, q->vector->y, q->vector->z);
		ft_printf("q_m:\t%f (%f, %f, %f)\n", q_matrix->w, q_matrix->vector->x, q_matrix->vector->y, q_matrix->vector->z);

		get_ndc_coords(cam_data, cam, scene->res, q, pos, scene, mlx_ptr, win_ptr, base, inc_x, inc_y);
	// get_fisheye_ndc_coords(scene);
}

// void trace_them_rays(t_rt_scene *scene)
// {
// 	t_qua *q = determine_quaternion(gen_coord(0,1,0), gen_coord(0,0,-1));
// 	ft_printf("q: %f, %f, %f, %f\n", q->w, q->vector->x, q->vector->y, q->vector->z);
// 	t_vec *v = orient_vector(q, gen_coord(1,0,0));
// }


t_camera *find_cam(t_camera *cam_orig, int i)
{
	t_camera *cam_new;
	int j = 0;

	cam_new = cam_orig;
	if (i < 0)
		return (NULL);
	if (i == 0)
		return (cam_orig);
	while(j != i && cam_new->next != NULL)
	{
		ft_printf("j: %d, i: %d\n", j, i);
		cam_new = cam_new->next;
		j++;
	}
	return (cam_new);
}


int	deal_key(int key, void *mlx_data)
{
	t_mlx_data **data = (t_mlx_data **)mlx_data;
	ft_printf("actual i: %d\n", (*data)->i);
	t_rt_scene *scene = (*data)->scene;
	t_camera *cam_orig = scene->cam;
	t_camera *cam_cur = NULL;
	int i = (*data)->i;
	ft_printf("key: %d\n", key);
	if (cam_orig == NULL)
	{
		return (0);
	}
	else
	{
		// ft_printf("cam: %p\n", cam_orig);
		// ft_printf("%d\n", key);
		if (key == 65363 || key == 124)//65363 for windows
		{
			if (i < (*data)->cam_amt)
				i++;
		}
		else if (key == 65361 || key == 123)//65361 for windows
		{
			if (i > 0)
				i--;
		}
		else
		{
			ft_printf("invalid key\n");
			return (0);
		}
		ft_printf("i: %d\n", i);
		cam_cur = find_cam(cam_orig, i);
		ft_printf("camera fov: %d\n", cam_cur->fov);
		(*data)->i = i;
		trace(scene, (*data)->mlx_ptr, (*data)->win_ptr, cam_cur);
	}
	// trace(scene, mlx_ptr, win_ptr, cam);
	return (0);
}

int	get_cam_amt(t_camera *cam_head)
{
	int amt;
	t_camera *cur;

	amt = 0;
	cur = cam_head;
	while(cur->next != NULL)
	{
		amt++;
		cur = cur->next;
	}
	return (amt);
}

void trace_them_rays(t_rt_scene *scene)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int y;
	int color;

	y = 100;
	t_mlx_data *mlx_data;
	mlx_data = (t_mlx_data *)e_malloc(sizeof(t_mlx_data));

	mlx_data->scene = scene;
	// ft_printf("sp color: (%d, %d, %d)", scene->obj->next->color->r, scene->obj->next->color->g, scene->obj->next->color->b);
	
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT);
	//direction vector for a straight vector for collision checking.
	// t_vec *dir = determine_vector(scene->cam->pos, scene->cam->orien);
	// ft_printf("vector: (%f, %f, %f)\n", dir->x, dir->y, dir->z);

	mlx_data->cam_amt = get_cam_amt(scene->cam);
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, scene->res->res_x, scene->res->res_y, "miniRT");
	mlx_data->i = 0;
	mlx_key_hook(mlx_data->win_ptr, deal_key, &mlx_data);
	trace(scene, mlx_data->mlx_ptr, mlx_data->win_ptr, scene->cam);

	//get straight vector
	//get position of current pixel
	//apply straight vector with current pixel to check for collision

	
	

	// color = translate_color(scene->amb->color);
	// ft_printf("%x\n", color);
	// while(y < 300)
	// {
	// 	mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 100, y, color);
	// 	color += 1;
	// 	y++;
	// }
	mlx_loop(mlx_data->mlx_ptr);
	// img_ptr = mlx_new_image(mlx_ptr, 12, 12);
}