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


int		translate_color(t_color *color);
t_vec	*determine_vector(t_vec *pos1, t_vec *pos2);
t_vec	*gen_coord(double x, double y, double z);
double	det_len_vec(t_vec *vector);
t_vec	*set_vec_len(t_vec *vector, double len);
int		within_grid(t_vec *pos, t_grid *grid);

#endif