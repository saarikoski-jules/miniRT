# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko      #+#    #+#                  #
#    Updated: 2020/06/14 16:36:11 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PARSE_DIR = parsing/
RENDER_DIR = rendering/
RT_SRCS =	test.c \
			error.c \
			\
			$(PARSE_DIR)parse.c \
			$(PARSE_DIR)parse_environment.c \
			$(PARSE_DIR)parse_obj.c \
			$(PARSE_DIR)get_objects.c \
			$(PARSE_DIR)parse_utils.c \
			$(PARSE_DIR)parse_validation.c \
			\
			$(RENDER_DIR)render.c \
			$(RENDER_DIR)mlx_manage.c \
			$(RENDER_DIR)save_bmp.c \
			$(RENDER_DIR)key_input.c \
			$(RENDER_DIR)select_cam.c \
			$(RENDER_DIR)cam_info.c \
			$(RENDER_DIR)gen_rays.c \
			$(RENDER_DIR)render_utils.c \
			$(RENDER_DIR)vector_utils.c \
			$(RENDER_DIR)quaternion.c \
			$(RENDER_DIR)orient_vec.c \
			$(RENDER_DIR)collision_2d.c \
			$(RENDER_DIR)collision_sp.c \
			$(RENDER_DIR)collision_cy.c \
			$(RENDER_DIR)color.c \
			$(RENDER_DIR)normal.c \

MLXFLAGS_W = -lmlx -lXext -lX11
MLX_FLAGS_W = -lm -lmlx -lXext -lX11 -L ./libft -lft -lpthread
MLXFLAGS_M = -lmlx -framework OpenGL -framework AppKit


all:
	@make -C libft
	@gcc -Iincludes $(RT_SRCS) libft/libft.a -Ilibft -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

windows:
	@make -C libft
	@gcc -Iincludes $(RT_SRCS) libft/libft.a -Ilibft -Imlx_linux/minilibx-master -Lmlx_linux/minilibx-master $(MLX_FLAGS_W)

fclean:
	@rm -rf a.out
	@make -C libft fclean

re: fclean all
