# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 17:37:34 by jroguszk          #+#    #+#              #
#    Updated: 2018/05/01 15:19:53 by jroguszk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = main.c get_input.c shapes.c shape_arithmetic.c light.c allocate_coordinates.c rotate.c draw.c shadow.c

OBJ = $(SRC:.c=.o)

LIBFT = includes/libft/libft.a

HEADER = -c -I ray_tracer.h

all: $(NAME)

$(OBJ): %.o: %.c
		@gcc -c -Wall -Werror -Wextra -I includes/libft/ $< -o $@

$(LIBFT):
	@make -C includes/libft

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(OBJ) $(LIBFT) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

clean:
	/bin/rm -f $(OBJ)
	@make -C includes/libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C includes/libft fclean

re: fclean all
