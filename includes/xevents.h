/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   xevents.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 14:20:44 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/06/13 12:38:15 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef XEVENTS_H
# define XEVENTS_H


// #define XK_KP_Left                       0xff96
// #define XK_KP_Up                         0xff97
// #define XK_KP_Right                      0xff98
// #define XK_KP_Down                       0xff99
// #define XK_Escape                        0xff1b

//keycodes
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_ESC 53

//events
# define DESTROY_NOTIFY 17


//masks
# define SUBSTRUCTURE_NOTIFY_MASK 1L<<19




#endif