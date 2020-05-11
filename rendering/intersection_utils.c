/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 13:32:42 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/05/11 13:34:28 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	solve_quadratic(double a, double b, double c, double multiple)
{
	double disc;
	double t;
	double t1;
	double t2;

	disc = pow(b, 2) - multiple * a * c;
	t = -1;
	if (disc < 0)
		return (-1.0);
	if (disc > 0)
	{
		t1 = (((-b) - sqrt(disc)) / 2);
		t2 = (((-b) + sqrt(disc)) / 2);
		if (t1 < t2)
			t = t1;
		else
			t = t2;
	}
	else if (disc == 0)
		t = (-1 * b) / (2 * a); //should be the same as d = -0.5 * b
		//get normal
	return (t);
}

