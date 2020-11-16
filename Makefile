# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 18:43:13 by yelazrak          #+#    #+#              #
#    Updated: 2020/11/16 17:11:55 by mobouzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

c_srcs = machine_virtuelle/main.o \
		machine_virtuelle/calcul.o \
		machine_virtuelle/arena.o \
		machine_virtuelle/init.o \
		machine_virtuelle/read_file.o \
		machine_virtuelle/exec.o \
		machine_virtuelle/tool.o \
		instructoin_assembly/ld.o \
		instructoin_assembly/st.o \
		instructoin_assembly/ldi.o \
		instructoin_assembly/and.o \
		instructoin_assembly/sti.o\
		instructoin_assembly/live.o\
		instructoin_assembly/add.o \
		instructoin_assembly/aff.o \
		instructoin_assembly/fork.o  \
		instructoin_assembly/lfork.o \
		instructoin_assembly/lld.o  \
		instructoin_assembly/lldi.o\
		instructoin_assembly/or.o \
		instructoin_assembly/sub.o \
		instructoin_assembly/xor.o \
		instructoin_assembly/zjmp.o\

VISU =  visualizer/arena_viewer.o \
		visualizer/menu_viewer.o \

INCLUDES = ./include
CFLAGS = -Wall -Wextra -Werror -g
CC=gcc
all: libft_ $(NAME)

libft_:
	@make -C libft

$(NAME): $(c_srcs) $(VISU) libft/libft.a
	$(CC) -o $(NAME) $(FLAGS) $(c_srcs) -lncurses $(VISU) -L ./libft -lft -I $(INCLUDES)

clean:
	@make clean -C libft
	@rm -rf $(c_srcs)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
