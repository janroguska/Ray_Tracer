# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 17:37:34 by jroguszk          #+#    #+#              #
#    Updated: 2018/04/25 14:26:12 by jroguszk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = main.c get_input.c shapes.c light.c shape_arithmetic.c

OBJ = $(SRC:.c=.o)

LIBFT = includes/libft/libft.a

MINILIBX = minilibx/libmlx.a

HEADER = -c -I ray_tracer.h

all: $(NAME)

$(OBJ): %.o: %.c
		@gcc -c -Wall -Werror -Wextra -I includes/libft/ $< -o $@

$(LIBFT):
	@make -C includes/libft

$(MINILIBX):
	@make -C minilibx

$(NAME): $(LIBFT) $(OBJ) $(MINILIBX)
	@gcc $(OBJ) $(LIBFT) $(MINILIBX) -o $(NAME) -framework OpenGL -framework AppKit

clean:
	/bin/rm -f $(OBJ)
	@make -C includes/libft clean
	@make -C minilibx clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C includes/libft fclean
	@make -C minilibx clean

re: fclean all
