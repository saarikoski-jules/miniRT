/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:33:35 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/18 15:50:10 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include <stdlib.h>//for size_t

# define C_MAIN_FEW_ARGUMENTS 132
# define E_MAIN_FEW_ARGUMENTS "Too few arguments given. 1 needed."
# define C_INVALID_FILE 133
# define E_INVALID_FILE "Not a valid file."
# define C_PARSE 134
# define E_PARSE "Invalid formatting in file."
# define C_PARSE_INVALID_INT 135
# define E_PARSE_INVALID_INT "Can't parse int."
# define C_PARSE_INVALID_FLOAT 136
# define E_PARSE_INVALID_FLOAT "Can't parse float."
# define C_PARSE_NO_COMMA 137
# define E_PARSE_NO_COMMA "Comma not found."
# define C_INVALID_ORIEN_VEC 138
# define E_INVALID_ORIEN_VEC "Invalid format for orientation vector."
# define C_INVALID_FOV 139
# define E_INVALID_FOV "Invalid format for fov."
# define C_INVALID_CAM 140
# define E_INVALID_CAM "Invalid format for camera."
# define C_INVALID_LIGHT 141
# define E_INVALID_LIGHT "Invalid format for light."
# define C_INVALID_COLOR 142
# define E_INVALID_COLOR "Invalid format for color."
# define C_INVALID_RES 143
# define E_INVALID_RES "Invalid format for resolution."
# define C_INVALID_AMB 144
# define E_INVALID_AMB "Invalid format for ambiance."
# define C_INVALID_OBJ 145
# define E_INVALID_OBJ "Invalid format for object."
# define C_INVALID_SP 146
# define E_INVALID_SP "Invalid format for sphere."
# define C_INVALID_SQ 147
# define E_INVALID_SQ "Invalid format for square."
# define C_INVALID_CY 148
# define E_INVALID_CY "Invalid format for cylinder."
# define C_NO_RES 149
# define E_NO_RES "Resolution not defined."
# define C_NO_AMB 150
# define E_NO_AMB "Ambiance not defined."
# define C_NO_CAM 151
# define E_NO_CAM "No cameras defined."
# define C_NO_CONNECT 152
# define E_NO_CONNECT "Wasn't able to establish connection to graphics server."
# define C_R_INVALID_VEC 153
# define E_R_INVALID_VEC "Invalid vector"
# define C_R_INVALID_ARG_Q 154
# define E_R_INVALID_ARG_Q "Invalid arguments in determine_quaternion"

void	error_exit_errno(void);
void	error_exit_msg(const unsigned int e_code, const char *e_msg);
void	*e_malloc(size_t size);

#endif
