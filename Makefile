# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko       #+#    #+#                 #
#    Updated: 2020/03/15 15:45:26 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RT_SRCS =	test.c

all:
	@make -C libft
	@gcc -Iincludes $(RT_SRCS) libft/libft.a -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

fclean:
	@rm -rf a.out
	@make -C libft fclean

re: fclean all
