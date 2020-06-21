/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 19:40:09 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 19:40:09 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

t_vec			*gen_coord(double x, double y, double z);
t_vec			*determine_vector(t_vec *pos1, t_vec *pos2);
t_vec			*set_vec_len(t_vec *vector, double len);
double			det_len_vec(t_vec *vector);
t_vec			*add_vectors(t_vec *vec1, t_vec *vec2);
t_vec			*substract_vectors(t_vec *vec1, t_vec *vec2);
double			get_dot_product(t_vec *vec1, t_vec *vec2);
t_vec			*get_cross_product(t_vec *vec1, t_vec *vec2);

#endif
