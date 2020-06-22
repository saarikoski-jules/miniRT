/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 19:34:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/22 15:46:37 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "rt.h"
# include <stdlib.h>

# define EPSILON 0.0000001
# define NO_INTERSECT -1
# define INSIDE_OBJ -2

typedef struct			s_screen_details
{
	double				aspect_ratio;
	double				len_x;
	double				len_y;
	double				inc_x;
	double				inc_y;
}						t_screen_details;

typedef struct			s_cam_info
{
	t_screen_details	*screen;
	t_camera			*cam;
	t_vec				*cam_right;
	t_vec				*cam_up;
}						t_cam_info;

typedef struct			s_mlx_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	int					i;
	t_vec				*cur_orien;
	int					cam_amt;
	t_rt_scene			*scene;
	t_cam_info			*cam_info;
}						t_mlx_data;

typedef struct			s_image_data
{
	char				**image;
	int					size_line;
	int					bpp;
}						t_image_data;

typedef struct			s_iterators
{
	size_t				i;
	size_t				j;
	size_t				pix_pos;
}						t_iterators;

double					cy_intersect(t_vec *start, t_vec *ray, t_cy *cy);
double					sp_intersect(t_vec *start, t_vec *ray, t_sp *sp);
double					tr_intersect(t_vec *start, t_vec *ray, t_tr *tr);
double					sq_intersect(t_vec *start, t_vec *ray, t_sq *sq);
double					pl_intersect(t_vec *orien, t_vec *ray_start, t_vec *pos,
							t_vec *ray);
void					manage_window(t_mlx_data *mlx_data);
t_mlx_data				*init_mlx_data(t_rt_scene *scene);
t_cam_info				*gen_cam_data(t_rt_scene *scene, t_camera *cam);
void					save_img(t_rt_scene *scene, t_cam_info *cam_info,
							const char *path);
char					*save_image(t_cam_info *cam_data, t_rt_scene *scene);
void					gen_image(t_cam_info *cam_data, t_rt_scene *scene,
						t_image_data *img_data);
t_color					*calculate_final_color(t_rt_scene *scene, t_vec **point,
							t_obj *obj, t_camera *cam);
t_vec					*calculate_normal(t_obj *obj, t_vec *intersect,
							t_camera *cam);
t_color					*ray_intersect(t_rt_scene *scene, t_vec *ray,
							t_camera *cam);
void					render_image(t_mlx_data *mlx_data,
							t_cam_info *cam_info);
double					check_obj_intersect(t_obj *obj_tmp, t_vec *ray,
							t_vec *pos, double d_tmp);
void					rotate_camera(int key, t_mlx_data **data, int cam_index);

#endif
