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
// int		within_grid(t_vec *pos, t_grid *grid);

#endif