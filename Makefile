# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko       #+#    #+#                 #
#    Updated: 2020/03/15 16:08:06 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RT_SRCS =	test.c \
			parse.c \

all:
	@make -C libft
	@gcc -Iincludes -Ilibft $(RT_SRCS) libft/libft.a -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

windows:
	@make -C libft
	@gcc -Iincludes -Ilibft $(RT_SRCS) libft/libft.a -Imlx

fclean:
	@rm -rf a.out
	@make -C libft fclean

re: fclean all
