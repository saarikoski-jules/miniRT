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

# define C_MAIN_FEW_ARGUMENTS 132
# define E_MAIN_FEW_ARGUMENTS "Too few arguments given. 1 needed."

# define C_PARSE 133
# define E_PARSE "Invalid .rt file"
# define C_INVALID_ORIEN_VEC 12
# define E_INVALID_ORIEN_VEC "Invalid format for orientation vector."
# define C_INVALID_FOV 13
# define E_INVALID_FOV "Invalid format for fov."
# define C_INVALID_CAM 14
# define E_INVALID_CAM "Invalid format for camera."

# define C_PARSE_INVALID_INT 134
# define E_PARSE_INVALID_INT "Can't parse int"

# define C_PARSE_INVALID_FLOAT 135
# define E_PARSE_INVALID_FLOAT "Can't parse float"

# define C_PARSE_NO_COMMA 136
# define E_PARSE_NO_COMMA "Comma not found"

void	error_exit_errno(void);
void	error_exit_msg(const unsigned int e_code, const char *e_msg);
void	validate_int(char *line);
void	validate_float(char *line);

#endif
