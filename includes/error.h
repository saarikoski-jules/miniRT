/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 18:33:35 by jvisser        #+#    #+#                */
/*   Updated: 2020/03/15 18:45:29 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define C_FEW_ARGUMENTS 10
# define E_FEW_ARGUMENTS "Too few arguments given. 1 needed."

void	error_exit_msg(const unsigned int e_code, const char *e_msg);

#endif
