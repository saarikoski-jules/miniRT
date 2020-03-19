# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko       #+#    #+#                 #
#    Updated: 2020/03/18 15:47:14 by jvisser       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PARSE_DIR = parsing/
RT_SRCS =	test.c \
			error.c \
			\
			$(PARSE_DIR)parse.c \
			$(PARSE_DIR)parse_environment.c \
			$(PARSE_DIR)parse_obj.c \
			$(PARSE_DIR)get_objects.c \
			$(PARSE_DIR)parse_vec.c \
			$(PARSE_DIR)parse_utils.c \
			$(PARSE_DIR)parse_validation.c \

all:
	@make -C libft
	@gcc -Iincludes $(RT_SRCS) libft/libft.a -Ilibft -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

windows:
	@make -C libft
	@gcc -Iincludes -Ilibft $(RT_SRCS) libft/libft.a -Imlx

fclean:
	@rm -rf a.out
	@make -C libft fclean

re: fclean all
