# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djeon <student.42seoul.kr>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/03 14:22:20 by mac               #+#    #+#              #
#    Updated: 2021/02/22 16:36:15 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXPATH = minilibx_opengl_20191021
MMSPATH = minilibx_mms_20200219
MLX = libmlx.dylib
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h
SRC = main.c \
	ft_cub3d_draw.c \
	ft_cub3d_draw_wall.c \
	ft_cub3d_moving.c \
	ft_cub3d_moving_sub.c \
	ft_cub3d_moving_sub2.c \
	ft_cub3d_parse.c \
	ft_cub3d_parse_sub.c \
	ft_cub3d_parse_utils.c \
	ft_cub3d_init.c \
	ft_cub3d_utils.c \
	ft_cub3d_utils2.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_split.c \
	ft_strncmp.c \
	bmp.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L$(MLXPATH) $(LXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
