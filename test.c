/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/14 14:09:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/11 15:42:53 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"//
// #include "mlx.h"
#include "error.h"
#include "libft.h"
#include "rt.h"
#include <fcntl.h>//

void print_scene(t_rt_scene *scene)
{
	t_light *cur_light;
	t_camera *cur_cam;
	t_obj *cur_obj;
	size_t i;

	cur_light = scene->light;
	cur_cam = scene->cam;
	cur_obj = scene->obj;
	ft_printf("resolution: (%d, %d)\n\nambiance:\n\tratio:\t%f\n\tcolor\t(%d, %d, %d)\n\n", scene->res->res_x, scene->res->res_y, scene->amb->ratio, scene->amb->color->r, scene->amb->color->g, scene->amb->color->b);

	ft_printf("lights:\n");
	i = 1;
	while (cur_light != NULL)
	{
		if (cur_light != NULL)
		{
			ft_printf("\tlight%d:\n\tposition:\t(%f, %f, %f)\n\tbrightness:\t%f\n\tcolor:\t\t(%d, %d, %d)\n\n", i, cur_light->pos->x, cur_light->pos->y, cur_light->pos->z, cur_light->brightness, scene->light->color->r, scene->light->color->g, scene->light->color->b);
			cur_light = cur_light->next;
			i++;
		}
	}

	ft_printf("cameras:\n");
	i = 1;
	while (cur_cam != NULL)
	{
		if (cur_cam != NULL)
		{
			ft_printf("\tcam%d:\n\tposition:\t(%f, %f, %f)\n\torientation:\t(%f, %f, %f)\n\tfov:\t\t%d\n\n", i, cur_cam->pos->x, cur_cam->pos->y, cur_cam->pos->z, cur_cam->orien->x, cur_cam->orien->y, cur_cam->orien->z, cur_cam->fov);
			cur_cam = cur_cam->next;
			i++;
		}
	}
	ft_printf("objects:\n");
	i = 1;
	while (cur_obj != NULL)
	{
		if (cur_obj != NULL)
		{
			ft_printf("\tobject%d\n", i);
			if (cur_obj->id == sp)
			{
				ft_printf("\tsphere position:\t(%f, %f, %f)\n\tsphere diameter:\t%f\n", cur_obj->type.sp->pos->x, cur_obj->type.sp->pos->y, cur_obj->type.sp->pos->z, cur_obj->type.sp->dia);
			}
			else if (cur_obj->id == pl)
			{
				ft_printf("\tplane position:\t\t(%f, %f, %f)\n\tplane orientation:\t(%f, %f, %f)\n", cur_obj->type.pl->pos->x, cur_obj->type.pl->pos->y, cur_obj->type.pl->pos->z, cur_obj->type.pl->orien->x, cur_obj->type.pl->orien->y, cur_obj->type.pl->orien->z);
				
			}
			else if (cur_obj->id == sq)
			{
				ft_printf("\tsquare position:\t(%f, %f, %f)	\n\tsquare orientation:\t(%f, %f, %f)\n\tlength of side:\t\t%f\n", cur_obj->type.sq->pos->x, cur_obj->type.sq->pos->y, cur_obj->type.sq->pos->z, cur_obj->type.sq->orien->x, cur_obj->type.sq->orien->y, cur_obj->type.sq->orien->z, cur_obj->type.sq->side);

			}
			else if (cur_obj->id == cy)
			{
				ft_printf("\tcylinder position:\t(%f, %f, %f)\n\tcylinder orientation:\t(%f, %f, %f)\n\tdiameter:\t\t%f\n\theight:\t\t\t%f\n", cur_obj->type.cy->pos->x, cur_obj->type.cy->pos->y, cur_obj->type.cy->pos->z, cur_obj->type.cy->orien->x, cur_obj->type.cy->orien->y, cur_obj->type.cy->orien->z, cur_obj->type.cy->dia, cur_obj->type.cy->h);

			}
			else if (cur_obj->id == tr)
			{
				ft_printf("\ttriangle corner1:\t(%f, %f, %f)\n\ttriangle corner2:\t(%f, %f, %f)\n\ttriangle corner3:\t(%f, %f, %f)\n", cur_obj->type.tr->point1->x, cur_obj->type.tr->point1->y, cur_obj->type.tr->point1->z, cur_obj->type.tr->point2->x, cur_obj->type.tr->point2->y, cur_obj->type.tr->point2->z, cur_obj->type.tr->point3->x, cur_obj->type.tr->point3->y, cur_obj->type.tr->point3->z);

			}
			ft_printf("\tcolor:\t\t\t(%d, %d, %d)\n\n", cur_obj->color->r, cur_obj->color->g, cur_obj->color->b);

			cur_obj = cur_obj->next;
			i++;
		}
	}
	
}

// void trace_them_rays(t_rt_scene *scene)
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// 	void *img_ptr;
// 	int y;
// 	int color;

// 	y = 100;
// 	color = 0xff0000;
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		error_exit_msg(C_NO_CONNECT, E_NO_CONNECT);
// 	win_ptr = mlx_new_window(mlx_ptr, scene->res->res_x, scene->res->res_y, "title");
// 	while(y < 300)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, 100, y, color);
// 		color += 1;
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// 	img_ptr = mlx_new_image(mlx_ptr, 12, 12);
// }

// typedef struct{
//     uint8_t signature[2];
//     uint32_t filesize;
//     uint32_t reserved;
//     uint32_t fileoffset_to_pixelarray;
// } fileheader;
// typedef struct{
//     uint32_t dibheadersize;
//     uint32_t width;
//     uint32_t height;
//     uint16_t planes;
//     uint16_t bitsperpixel;
//     uint32_t compression;
//     uint32_t imagesize;
//     uint32_t ypixelpermeter;
//     uint32_t xpixelpermeter;
//     uint32_t numcolorspallette;
//     uint32_t mostimpcolor;
// } bitmapinfoheader;
// typedef struct {
//     fileheader fileheader;
//     bitmapinfoheader bitmapinfoheader;
// } bitmap;



// typedef struct	s_bitmap_header
// {
	// t_file_header	file_header;
	// t_info_header	info_header;
// }				t_bitmap_header;


// t_file_header gen_file_header()
// {

// 	return (file_header);
// }

// t_info_header gen_info_header()
// {
// 	return (info_header);
// }

// int	input_header(int fd, t_bitmap_header header)
// {
	// return (0);
// }


// typedef struct	s_file_header
// {
// 	uint8_t		file_type1; //BM (should i do two uint8 for B and M ?)
// 	uint8_t		file_type2; //BM (should i do two uint8 for B and M ?)
// 	uint32_t	file_size; //? 54 bytes header + pixels
// 	uint16_t	reserved; //0
// 	uint16_t	reserved2; //maybe you dont need this and they can be one uint32 with value 0
// 	uint32_t	pixel_offset; // 54? AAA 14 bytes for file header + 40 bytes for info header
// }				t_file_header;

// typedef struct	s_info_header
// {
// 	uint32_t	info_header_size; //40
// 	uint32_t	pixel_x; //res_x
// 	uint32_t	pixel_y; //res_y
// 	uint16_t	planes; //1 ????
// 	uint16_t	bits_per_pixel; //24 ??
// 	uint32_t	compression; // 0 (no compression used)
// 	uint32_t	img_size; //when no compression used can be set to 0 ????
// 	uint32_t	pix_p_meter_x; //can be set to 0 ????
// 	uint32_t	pix_p_meter_y; //can be set to 0 ????
// 	uint32_t	colors; //can be set to 0
// 	uint32_t	important_colors; //0 (all colors important)
// }				t_info_header;

int	gen_bmp_header(int fd, t_rt_scene *scene)
{
	char f_header[14];
	int bpp = 24; //get value from get_img_address or whatever that func is
	// int amt_pixels = scene->res->res_x * scene->res->res_y;
	int row_size = scene->res->res_x * (bpp / 8);

	// if (row_size % 4 == 0)
		// row_size += 4;
	// else
	// {
		while (row_size % 4 != 0)
		{
			ft_printf("pad\n");
			row_size++;
		}
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
	
	ft_printf("amt_bytes: %d\n", amt_bytes);
	ft_bzero(f_header, 14);

	f_header[0] = 'B'; //8 file type
	f_header[1] = 'M'; //16
	//might need a padding byte here??
	f_header[2] = (uint32_t)file_size; //16 + 32 = 48
	f_header[6] = (uint32_t)0; //reserved
	f_header[10] = (uint32_t)54; //pixel offset

	write(1, &f_header, 14);
	write(fd, &f_header, 14);

	char i_header[40];
	ft_bzero(i_header, 40);

	i_header[0] = (uint32_t)40; //header size
	i_header[4] = (uint32_t)scene->res->res_x; //res_x
	i_header[8] = (uint32_t)scene->res->res_y; //res_y
	i_header[12] = (uint16_t)1; //planes
	i_header[14] = (uint16_t)bpp; //bits per pixel
	i_header[16] = (uint32_t)0; //compression
	i_header[20] = (uint32_t)0; // img size, (can be set to 0 when no compression used)
	i_header[24] = (uint32_t)0; //pix per meter x (can be set to zero)
	i_header[28] = (uint32_t)0; //pix per meter y (can be set to zero)
	i_header[32] = (uint32_t)0; //colors (can be set to zero?)
	i_header[36] = (uint32_t)0; //important colors (0 means all colors are important)
	write(1, "\nlol\n", 5);

	write(1, &i_header, 40);//if write fails, exit
	write(fd, &i_header, 40);

	// fwrite(&f_header, 2, 1, fd);
	return (1);
}

int append_pixels(int fd)
{
	char str[4];
	ft_bzero(str, 4);
	write(fd, &str, 4);
	return(1);
}

int main(int ac, char **av)
{
	t_rt_scene	*scene;
	if (ac >= 2)
	{
		scene = get_scene(av[1]); //make sure anything but .rt works
		if (ac == 3 && ft_strncmp("--save", av[2], 7) == 0) //make sure there's a valid path
		{
			size_t len = ft_strlen(av[1]);
			char *name = ft_substr(av[1], 0, len - 3);
			char *name_bmp = ft_strjoin(name, ".bmp");
			ft_printf("%s\n", name_bmp);
			int fd = open(name_bmp, O_RDWR | O_CREAT | O_APPEND, 0666); //will not overwrite with new .bmp.
			size_t img_size = 1;
			gen_bmp_header(fd, scene); //i can move all this to trace em rays to loop over cameras
			// append_pixels(fd);
			trace_them_rays(scene, fd);
			close(fd);
			return (0);//
		}
		else if (ac == 2)
		{
			trace_them_rays(scene, -1);
		}		
	}
	else
		error_exit_msg(C_MAIN_FEW_ARGUMENTS, E_MAIN_FEW_ARGUMENTS);
	// else if (ac == 3 && ft_strncmp("--save", av[2]))
		// ft_printf("saving");
	
	// print_scene(scene);

	return (0);
}
