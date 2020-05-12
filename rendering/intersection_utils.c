/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 13:32:42 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/12 13:57:17 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	solve_quadratic(double a, double b, double c)
{
	double disc;
	double t;
	double t1;
	double t2;

	disc = pow(b, 2) - 4 * a * c;
	t = -1;
	if (disc < 0)
		return (-1.0);
	if (disc > 0)
	{
		t1 = (((-b) - sqrt(disc)) / (2 * a));
		t2 = (((-b) + sqrt(disc)) / (2 * a));
		if (t1 < t2)
			t = t1;
		else
			t = t2;
	}
	else if (disc == 0)
		t = -b / (2 * a); //should be the same as d = -0.5 * b
		//get normal
	return (t);
}

