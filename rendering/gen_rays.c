/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_rays.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 16:34:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 17:52:24 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include "error.h"
#include "color.h"
#include <stdlib.h>

t_vec	*build_ray(double pixel_x, double pixel_y, t_cam_info *cam_data)
{
	t_vec	*pos_x;
	t_vec	*pos_y;
	t_vec	*screen_pos;
	t_vec	*rotated_ray;
	t_vec	*ray_u;

	pos_x = gen_coord(pixel_x * cam_data->cam_right->x,
					pixel_x * cam_data->cam_right->y,
					pixel_x * cam_data->cam_right->z);
	pos_y = gen_coord(pixel_y * cam_data->cam_up->x,
					pixel_y * cam_data->cam_up->y,
					pixel_y * cam_data->cam_up->z);
	screen_pos = add_vectors(pos_x, pos_y);
	rotated_ray = add_vectors(screen_pos, cam_data->cam->orien);
	ray_u = set_vec_len(rotated_ray, 1);
	free(pos_x);
	free(pos_y);
	free(screen_pos);
	free(rotated_ray);
	return (ray_u);
}

t_color	*shoot_ray(t_rt_scene *scene, t_cam_info *cam_data,
					double pixel_x, double pixel_y)
{
	t_color	*color;
	t_vec	*ray;

	ray = build_ray(pixel_x, pixel_y, cam_data);
	color = ray_intersect(scene, ray, cam_data->cam);
	free(ray);
	return (color);
}

void	cpy_pixel(t_iterators *iters, char **image,
					t_cam_info *cam_data, t_rt_scene *scene)
{
	t_color	*rgb;
	double	pixel_x;
	double	pixel_y;
	double	ndc_y;
	double	ndc_x;

	ndc_x = cam_data->screen->inc_x / 2 + (cam_data->screen->inc_x * iters->i);
	ndc_y = cam_data->screen->inc_y / 2 + (cam_data->screen->inc_y * iters->j);
	pixel_x = (((ndc_x * 2) - 1) *
				cam_data->screen->aspect_ratio * cam_data->screen->len_x);
	pixel_y = (1 - (ndc_y * 2)) * cam_data->screen->len_y;
	rgb = shoot_ray(scene, cam_data, pixel_x, pixel_y);
	if (rgb == NULL)
		return ;
	ft_memcpy((*image) + iters->pix_pos, &rgb->b, 1);
	ft_memcpy((*image) + iters->pix_pos + 1, &rgb->g, 1);
	ft_memcpy((*image) + iters->pix_pos + 2, &rgb->r, 1);
	free(rgb);
}

void	gen_image(t_cam_info *cam_data, t_rt_scene *scene,
					t_image_data *img_data)
{
	t_iterators *iters;

	iters = (t_iterators *)e_malloc(sizeof(t_iterators));
	iters->i = 0;
	iters->j = 0;
	iters->pix_pos = 0;
	while (iters->j < scene->res->res_y)
	{
		iters->pix_pos = img_data->size_line * iters->j;
		while (iters->i < scene->res->res_x)
		{
			cpy_pixel(iters, img_data->image, cam_data, scene);
			iters->i++;
			iters->pix_pos = (iters->j * img_data->size_line +
							(iters->i * (img_data->bpp / 8)));
		}
		iters->i = 0;
		iters->j++;
	}
	free(iters);
	ft_printf("done\n");//
}
