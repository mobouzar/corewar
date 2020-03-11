# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 18:43:13 by yelazrak          #+#    #+#              #
#    Updated: 2020/03/10 11:30:14 by yelazrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

c_srcs = machine_virtuelle/ft_load.o \
			machine_virtuelle/ft_arena.o \
			machine_virtuelle/battlefield.o \
			instructoin_assembly/live.o\
			instructoin_assembly/add.o \
			instructoin_assembly/aff.o \
			instructoin_assembly/and.o \
			instructoin_assembly/fork.o  \
			instructoin_assembly/ld.o \
			instructoin_assembly/ldi.o \
			instructoin_assembly/lfork.o \
			instructoin_assembly/lld.o  \
			instructoin_assembly/lldi.o\
			instructoin_assembly/or.o \
			instructoin_assembly/st.o \
			instructoin_assembly/sti.o\
			instructoin_assembly/sub.o \
			instructoin_assembly/xor.o \
			instructoin_assembly/zjmp.o\

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
