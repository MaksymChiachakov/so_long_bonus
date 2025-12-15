# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 13:22:14 by mchiacha          #+#    #+#              #
#    Updated: 2025/12/08 15:27:22 by mchiacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = ./srcs/main.c ./srcs/flood_fill.c ./srcs/free.c ./srcs/handler.c \
		./srcs/init_player.c ./srcs/map_valide.c ./srcs/read_map.c \
		./srcs/render_map.c ./srcs/gnl.c ./srcs/flood_fill_utils.c \
		./srcs/read_map_utils.c ./srcs/handler_utils.c ./srcs/canva.c \
		./srcs/ft_printf.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

MLX_DIR = ./minilibx-linux
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_DIR)
	$(CC) $(OBJS) $(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make clean -C $(MLX_DIR)
	make -C $(LIBFT_DIR) fclean

fclean: clean
	$(RM) $(NAME)
	make clean -C $(MLX_DIR)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
