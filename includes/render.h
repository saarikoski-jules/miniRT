#ifndef RENDER_H
# define RENDER_H

# include "color.h"
# include "vec.h"

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
t_vec	*determine_vector(t_vec *pos1, t_vec *pos2);
t_vec	*gen_coord(double x, double y, double z);
double	det_len_vec(t_vec *vector);
t_vec	*set_vec_len(t_vec *vector, double len);
int		within_grid(t_vec *pos, t_grid *grid);
t_vec *add_vectors(t_vec *vec1, t_vec *vec2);
t_vec *substract_vectors(t_vec *vec1, t_vec *vec2);
// t_vec *multiply_vectors(t_vec *vec1, t_vec *vec2);
double get_dot_product(t_vec *vec1, t_vec *vec2);



#endif