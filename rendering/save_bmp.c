/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 16:24:03 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/19 11:47:52 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include "error.h"
#include <fcntl.h>

void	gen_f_header(int fd, int i_header_size, int amt_bytes)
{
	char	f_header[14];
	int		f_header_size;
	int		header_size;
	int		file_size;

	f_header_size = 14;
	header_size = f_header_size + i_header_size;
	file_size = amt_bytes + header_size;
	ft_bzero(f_header, 14);
	ft_memcpy(f_header, "BM", 2);
	ft_memcpy(f_header + 2, &file_size, 4);
	ft_memcpy(f_header + 10, &header_size, 4);
	e_write(fd, f_header, 14);
}

void	gen_i_header(t_rt_scene *scene, int fd, int bpp, int i_header_size)
{
	char	i_header[40];
	int		height;

	height = -scene->res->res_y;
	ft_bzero(i_header, 40);
	ft_memcpy(i_header, &i_header_size, 4);
	ft_memcpy(i_header + 4, &scene->res->res_x, 4);
	ft_memcpy(i_header + 8, &height, 4);
	i_header[12] = (uint16_t)1;
	ft_memcpy(i_header + 14, &bpp, 2);
	e_write(fd, i_header, 40);	
}

void	gen_bmp_header(int fd, t_rt_scene *scene, t_mlx_data *mlx_data)
{
	int		i_header_size;
	int		amt_bytes;
	char	*image;
	t_image_data	*img_data;

	img_data = (t_image_data *)e_malloc(sizeof(t_image_data));
	i_header_size = 40;
	img_data->bpp = 24;
	img_data->size_line = scene->res->res_x * (img_data->bpp / 8);
	while (img_data->size_line % 4 != 0)
		img_data->size_line++;
	amt_bytes = img_data->size_line * scene->res->res_y;
	image = (char *)e_malloc(amt_bytes);
	img_data->image = &image;
	ft_bzero(image, amt_bytes);
	gen_f_header(fd, i_header_size, amt_bytes);
	gen_i_header(scene, fd, img_data->bpp, i_header_size);
	gen_image(mlx_data->cam_info, mlx_data->scene, img_data); //if fails, exit??
	e_write(fd, image, amt_bytes); //check for bad return value
	free(image);
	free(img_data);
}

void	save_img(t_mlx_data *mlx_data, const char *path)
{
	size_t	len;
	char	*name;
	char	*name_bmp;
	int		fd;

	len = ft_strlen(path);
	name = ft_substr(path, 0, len - 3);
	name_bmp = ft_strjoin(name, ".bmp");
	fd = open(name_bmp, O_RDWR | O_CREAT | O_APPEND, 0666); //will not overwrite with new .bmp.
	gen_bmp_header(fd, mlx_data->scene, mlx_data); //i can move all this to trace em rays to loop over cameras
	close(fd);//i dont really even need to close this
	// free(name);
	// free(name_bmp);
	// free(path);
	system("leaks a.out");
	// ft_printf("gets here??");
	exit(0);
}