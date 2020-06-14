#ifndef RENDER_H
# define RENDER_H

# include "color.h"
# include "vec.h"
# include "rt.h"
# include "object.h"

# define EPSILON 0.0000001
# define NO_INTERSECT -1
# define INSIDE_OBJ -2

typedef struct	s_cam_info
{
	double		aspect_ratio;
	double		fov_ratio; //likely wont need this
	double		len_x;
	double		len_y;
	t_camera	*cam;
	t_vec		*screen_intersect; //i can construct this in ndc coords
	double		increment_x;
	double		increment_y;
	t_vec		*cam_right;
	t_vec		*cam_up;
	t_vec		*orien_u; //dont need this, please just normalize orientation in parsing
}				t_cam_info;

typedef struct	s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			i;
	int			cam_amt;
	t_rt_scene	*scene;
	t_cam_info	*cam_info;
}				t_mlx_data;


int		translate_color(t_color *color);
// double	circle(t_rt_scene *scene, t_sp *sp, t_vec *ray, t_vec **n);
// double	square(t_rt_scene *scene, t_sq *sq, t_vec *ray, t_vec **n);
// double	triangle(t_rt_scene *scene, t_tr *tr, t_vec *ray, t_vec **n);
double	cy_intersect(t_vec *start, t_vec *ray, t_cy *cy);
double	sp_intersect(t_vec *start, t_vec *ray, t_sp *sp);
double	tr_intersect(t_vec *start, t_vec *ray, t_tr *tr);
double	sq_intersect(t_vec *start, t_vec *ray, t_sq *sq);
double	pl_intersect(t_vec *orien, t_vec *ray_start, t_vec *pos, t_vec *ray);

// double	plane_intersect(t_rt_scene *scene, t_vec *start, t_vec *ray, t_pl *pl, t_vec **n);
// double	plane_intersect(t_rt_scene *scene, t_pl *pl, t_vec *ray, t_vec **n);

//color
t_color *calculate_final_color(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n, t_camera *cam);

//normal
t_vec *calculate_normal(t_obj *obj, t_vec *intersect, t_camera *cam);

//maybe put these elsewhere
void		manage_window(t_mlx_data *mlx_data);
t_mlx_data *init_mlx_data(t_rt_scene *scene);
t_cam_info	*trace(t_mlx_data *mlx_data, t_camera *cam);

// get_ndc_coords_save(tcam_info, mlx_data->cam_info->screen_intersect, mlx_data->scene, mlx_data->cam_info->increment_x, mlx_data->cam_info->increment_x, fd); //if fails, exit??
void get_ndc_coords_save(t_cam_info *cam_data, t_vec *pos, t_rt_scene *scene, double inc_x, double inc_y, int fd); // if write fails, exit instead of bad return
void get_ndc_coords(t_cam_info *cam_data, t_vec *pos, t_rt_scene *scene, void *mlx_ptr, void *win_ptr, double inc_x, double inc_y);


//




//utils
double solve_quadratic(double a, double b, double c);
t_vec *find_point(t_vec *start, t_vec *dir, double t);
double get_distance(t_vec *point1, t_vec *point2);
double point_within_line(t_vec *point1, t_vec *point2, t_vec *p, t_vec *orien);



#endif