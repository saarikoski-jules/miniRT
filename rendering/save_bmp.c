/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 16:24:03 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/14 17:28:13 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <limits.h>//
#include "rt.h"
#include "render.h"
#include "libft.h"
#include "error.h"
#include <stdlib.h>
#include <fcntl.h>

int	gen_bmp_header(int fd, t_rt_scene *scene, t_mlx_data *mlx_data)
{
	char f_header[14];
	int bpp = 24; //get value from get_img_address or whatever that func is
	// int amt_pixels = scene->res->res_x * scene->res->res_y;
	int row_size = scene->res->res_x * (bpp / 8);
	int height = -scene->res->res_y;
	// if (row_size % 4 == 0)
		// row_size += 4;
	// else
	// {
		while (row_size % 4 != 0)
			row_size++;
		// {
			// ft_printf("pad\n");
		// }
	// }
	ft_printf("row_size %d\n", row_size);
	ft_printf("mabe row? %d\n", ((bpp * scene->res->res_x) / 32) * 4);
	// int img_size = (bpp / 8) * amt_pixels;
	int f_header_size = 14;
	int i_header_size = 40;
	int header_size = f_header_size + i_header_size;
	// size_t file_size = 54 + img_size; //plus padding bytes
	int amt_bytes = row_size * scene->res->res_y;
	int file_size = amt_bytes + header_size;
	// long long l_file_size = row_size * scene->res->res_y + header_size;
	// if (l_file_size > INT_MAX)
		// ft_printf("too bigg\n");
	// int size = 
	ft_printf("x: %d, y: %d\n", scene->res->res_x, scene->res->res_y);
	ft_printf("amt_bytes: %d\n", amt_bytes);
	ft_printf("file size: %d\n", file_size);
	ft_bzero(f_header, 14);

	ft_memcpy(f_header, "BM", 2);
	ft_memcpy(f_header + 2, &file_size, 4);
	ft_memcpy(f_header + 10, &header_size, 4);
	// f_header[0] = 'B'; //8 file type
	// f_header[1] = 'M'; //16
	// might need a padding byte here??
	// f_header[2] = (uint32_t)file_size; //16 + 32 = 48
	// *((u_int32_t *)&f_header[0x02]) = (u_int32_t)file_size;
	// ft_memcpy(f_header + 2, &file_size, 4);
	// f_header[6] = (uint32_t)0; //reserved
	// f_header[10] = (uint32_t)54; //pixel offset

	// write(1, &f_header, 14);
	// ft_putbytes_fd(&f_header, 14, 1);

	char i_header[40];
	ft_bzero(i_header, 40);

	// i_header[0] = (uint32_t)40; //header size
	ft_memcpy(i_header, &i_header_size, 4);
	// i_header[4] = (uint32_t)scene->res->res_x; //res_x
	ft_memcpy(i_header + 4, &scene->res->res_x, 4);
	// i_header[8] = (uint32_t)scene->res->res_y; //res_y
	ft_memcpy(i_header + 8, &height, 4);
	i_header[12] = (uint16_t)1; //planes
	// ft_memcpy(i_header + 12, , 2);
	// i_header[14] = (uint16_t)bpp; //bits per pixel
	ft_memcpy(i_header + 14, &bpp, 2);
	// i_header[16] = (uint32_t)0; //compression
	// i_header[20] = (uint32_t)0; // img size, (can be set to 0 when no compression used)
	// i_header[24] = (uint32_t)0; //pix per meter x (can be set to zero)
	// i_header[28] = (uint32_t)0; //pix per meter y (can be set to zero)
	// i_header[32] = (uint32_t)0; //colors (can be set to zero?)
	// i_header[36] = (uint32_t)0; //important colors (0 means all colors are important)
	write(1, "\nlol\n", 5);

	// write(1, &i_header, 40);//if write fails, exit
	// ft_putbytes_fd(&i_header, 40, 1);
	write(fd, f_header, 14);
	write(fd, i_header, 40);
	char *image = (char *)e_malloc(amt_bytes);
	ft_bzero(image, amt_bytes);
	gen_image(mlx_data->cam_info, mlx_data->scene, &image, row_size, bpp); //if fails, exit??
	write(fd, image, amt_bytes); //check for bad return value

	// fwrite(&f_header, 2, 1, fd);
	return (1);
}

void	save_img(t_mlx_data *mlx_data, const char *path)
{
	size_t len = ft_strlen(path);
	char *name = ft_substr(path, 0, len - 3);
	char *name_bmp = ft_strjoin(name, ".bmp");
	ft_printf("%s\n", name_bmp);
	int fd = open(name_bmp, O_RDWR | O_CREAT | O_APPEND, 0666); //will not overwrite with new .bmp.
	size_t img_size = 1;
	gen_bmp_header(fd, mlx_data->scene, mlx_data); //i can move all this to trace em rays to loop over cameras
	// append_pixels(fd);
	// t_cam_info *cam_data = trace(mlx_data, mlx_data->scene->cam, fd);
	//TODO: Call gen_cam_data from here, write to img here?
	// get_ndc_coords_save(cam_data, mlx_data->scene->cam, mlx_data->scene->res, pos, mlx_data->scene, mlx_data->mlx_ptr, mlx_data->win_ptr, base, inc_x, inc_y, fd); //if fails, exit??
	
	close(fd);
}