# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 18:43:13 by yelazrak          #+#    #+#              #
#    Updated: 2020/03/07 21:50:53 by yelazrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

c_srcs = machine_virtuelle/ft_load.o \
			 machine_virtuelle/ft_arena.o

INCLUDES = ./include
CFLAGS = -Wall -Wextra -Werror -g
CC=gcc
all: libft_ $(NAME)

libft_:
	@make -C libft

$(NAME): $(c_srcs)  libft/libft.a
	gcc -o $(NAME) $(FLAGS) $(c_srcs) -L ./libft -lft -I $(INCLUDES)
clean:
	@make clean -C libft
	@rm -rf $(c_srcs)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
