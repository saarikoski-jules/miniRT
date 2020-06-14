/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_rays.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 16:34:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/14 18:17:29 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>
#include "libft.h"//
#include "error.h"

//TODO: Do i actually need rt.h?? edit shit pls

t_color *shoot_ray(t_rt_scene *scene, double pixel_x, double pixel_y, t_cam_info *cam_data)
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
	return (ray_intersect(scene, ray_u, cam_data->cam));
}

void cpy_pixel(int i, int j, char **image, int pix_pos, t_cam_info *cam_data, t_rt_scene *scene)
{
	t_color *rgb;
	double	pixel_x;
	double	pixel_y;
	double ndc_y;
	double ndc_x;

	ndc_x = cam_data->screen->inc_x / 2 + (cam_data->screen->inc_x * i);
	ndc_y = cam_data->screen->inc_y / 2 + (cam_data->screen->inc_y * j);
	pixel_x = ((ndc_x * 2) - 1) * cam_data->screen->aspect_ratio * cam_data->screen->len_x;
	pixel_y = (1 - (ndc_y * 2)) * cam_data->screen->len_y;
	rgb = shoot_ray(scene, pixel_x, pixel_y, cam_data);
	if (rgb == NULL)
		return ;
	ft_memcpy((*image) + pix_pos, &rgb->b, 1);
	ft_memcpy((*image) + pix_pos + 1, &rgb->g, 1);
	ft_memcpy((*image) + pix_pos + 2, &rgb->r, 1);
	free(rgb);
}

void gen_image(t_cam_info *cam_data, t_rt_scene *scene, char **image, int size_line, int bpp)
{
	size_t	i;
	size_t	j;
	int		pix_pos;

	i = 0;
	j = 0;
	pix_pos = 0;
	while (j < scene->res->res_y)
	{
		pix_pos = size_line * j * i;
		while (i < scene->res->res_x)
		{
			cpy_pixel(i, j, image, pix_pos, cam_data, scene);
			i++;
			pix_pos = (j * size_line + (i * (bpp / 8)));
		}
		i = 0;
		j++;
	}
	ft_printf("done\n");
}
