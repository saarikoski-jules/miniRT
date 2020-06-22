# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsaariko <jsaariko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/14 14:09:55 by jsaariko      #+#    #+#                  #
#    Updated: 2020/06/22 15:21:06 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs/
PARSE_DIR = parsing/
RENDER_DIR = rendering/
NAME = miniRT
LIBFT = libft/libft.a
RT_SRCS =	$(SRCS_DIR)main.c \
			$(SRCS_DIR)error.c \
			\
			$(SRCS_DIR)$(PARSE_DIR)parse.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_environment.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_camera.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_obj.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_cy.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_sq.c \
			$(SRCS_DIR)$(PARSE_DIR)get_objects.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_utils.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_number.c \
			$(SRCS_DIR)$(PARSE_DIR)parse_validation.c \
			\
			$(SRCS_DIR)$(RENDER_DIR)render.c \
			$(SRCS_DIR)$(RENDER_DIR)mlx_manage.c \
			$(SRCS_DIR)$(RENDER_DIR)save_bmp.c \
			$(SRCS_DIR)$(RENDER_DIR)key_input.c \
			$(SRCS_DIR)$(RENDER_DIR)select_cam.c \
			$(SRCS_DIR)$(RENDER_DIR)cam_info.c \
			$(SRCS_DIR)$(RENDER_DIR)gen_rays.c \
			$(SRCS_DIR)$(RENDER_DIR)render_utils.c \
			$(SRCS_DIR)$(RENDER_DIR)vector_utils.c \
			$(SRCS_DIR)$(RENDER_DIR)math_utils.c \
			$(SRCS_DIR)$(RENDER_DIR)color_utils.c \
			$(SRCS_DIR)$(RENDER_DIR)quaternion.c \
			$(SRCS_DIR)$(RENDER_DIR)multiply_quaternions.c \
			$(SRCS_DIR)$(RENDER_DIR)quaternion_utils.c \
			$(SRCS_DIR)$(RENDER_DIR)orient_vec.c \
			$(SRCS_DIR)$(RENDER_DIR)collision_2d.c \
			$(SRCS_DIR)$(RENDER_DIR)collision_sp.c \
			$(SRCS_DIR)$(RENDER_DIR)collision_cy.c \
			$(SRCS_DIR)$(RENDER_DIR)color.c \
			$(SRCS_DIR)$(RENDER_DIR)normal.c \
			$(SRCS_DIR)$(RENDER_DIR)slerp.c \

RT_O_FILES = $(RT_SRCS:%.c=%.o)
MLXFLAGS_M = -Lmlx -lmlx -framework OpenGL -framework AppKit
INCLUDE = -Iincludes -Ilibft -Imlx
ERROR_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@echo "compiled $@"
	@gcc $(INCLUDE) $(ERROR_FLAGS) -c $< -o $@

$(NAME): $(RT_O_FILES)
	@make -C libft
	@make -C mlx
	@cp mlx/libmlx.dylib .
	@gcc $(MLXFLAGS_M) $(RT_O_FILES) $(LIBFT) -o $(NAME)
	@echo "Compiled miniRT"

windows:
	@make -C libft
	@gcc -Iincludes $(RT_SRCS) libft/libft.a -Ilibft \
		 -Imlx_linux/minilibx-master -Lmlx_linux/minilibx-master $(MLX_FLAGS_W)

clean:
	@make -C libft clean > /dev/null
	@make -C mlx clean > /dev/null
	@rm -f $(RT_O_FILES)
	@echo "Cleared object files"

fclean: clean
	@make -C libft fclean > /dev/null
	@rm -f libmlx.dylib
	@rm -f miniRT
	@echo "All clean!"

re: fclean all
