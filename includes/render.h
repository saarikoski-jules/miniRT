#ifndef RENDER_H
# define RENDER_H

# include "color.h"
# include "vec.h"
# include "rt.h"
# include "object.h"

typedef struct	s_grid
{
	t_vec	*up_left;
	t_vec	*up_right;
	t_vec	*down_left;
	t_vec	*down_right;
}				t_grid;

typedef struct	s_cam_info
{
	double	aspect_ratio;
	double	fov_ratio;
	double	len_x;
	double	len_y;
}				t_cam_info;

int		translate_color(t_color *color);
double	circle(t_rt_scene *scene, t_sp *sp, t_vec *ray, t_vec **n);
double	square(t_rt_scene *scene, t_sq *sq, t_vec *ray, t_vec **n);
double	triangle(t_rt_scene *scene, t_tr *tr, t_vec *ray, t_vec **n);
double	cylinder(t_rt_scene *scene, t_vec *start, t_vec *ray, t_cy *cy, t_vec **n);
double	plane_intersect(t_rt_scene *scene, t_pl *pl, t_vec *ray, t_vec **n);
t_color *calculate_final_color(t_rt_scene *scene, t_vec *ray, t_color *color, double d, t_obj *obj, t_vec *n);


#endif