/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 17:01:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 19:27:20 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_color_int
{
	int				r;
	int				g;
	int				b;
}					t_color_int;

int					translate_color(t_color *color);
t_color				*gen_color(int r, int g, int b);

#endif
