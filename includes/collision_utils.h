/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 16:53:32 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 17:01:04 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_UTILS_H
# define COLLISION_UTILS_H
//utils
double solve_quadratic(double a, double b, double c);
t_vec *find_point(t_vec *start, t_vec *dir, double t);
double get_distance(t_vec *point1, t_vec *point2);
double point_within_line(t_vec *point1, t_vec *point2, t_vec *p, t_vec *orien);

#endif