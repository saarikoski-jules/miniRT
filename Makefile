# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko       #+#    #+#                 #
#    Updated: 2020/03/14 19:49:16 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# all:
	# gcc test.c -Imlx -L mlx/ -lmlx -framework OpenGL -framework AppKit


all:
	cc -I /mlx test.c -L /mlx -lmlx -framework OpenGL -framework AppKit
	
	# gcc test.c -Imlx -L mlx/ -lmlx -framework OpenGL -framework AppKit 

	# gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit