/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_cameras.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 13:13:35 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/14 16:15:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_CAMERAS_H
# define MANAGE_CAMERAS_H

#include "rt.h"// ??
#include "render.h"//

int	get_cam_amt(t_camera *cam_head);
t_camera *find_cam(t_camera *cam_orig, int i);
int select_cam(int key, t_mlx_data *data);

t_cam_info	*gen_cam_data(t_mlx_data *mlx_data, t_camera *cam);


#endif