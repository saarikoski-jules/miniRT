/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_functions.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 12:50:56 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/21 16:43:12 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_FUNCTIONS_H
# define KEY_FUNCTIONS_H

int close_program(void *mlx_data);
// int expose(void *mlx_data);//when you click on your window and it comes out from behind another window //TODO: find out if i need this for smooth moving and exposing the window
int	deal_key(int key, void *mlx_data); //TODO: make separate header file for key event function pointers

#endif