# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko       #+#    #+#                 #
#    Updated: 2020/03/15 14:15:14 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# all:
	# gcc test.c -Imlx -L mlx/ -lmlx -framework OpenGL -framework AppKit
	# gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
	# gcc test.c -Imlx -L mlx/ -lmlx -framework OpenGL -framework AppKit 

# LIBFT_DIR = libft/

all:
	make -C libft
	gcc -Imlx test.c libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit

fclean:
	rm a.out
	make -C libft fclean

re: fclean all
