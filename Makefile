# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 08:59:28 by tglaudel          #+#    #+#              #
#    Updated: 2016/06/02 11:51:40 by tglaudel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/

SRC_NAME = main.c \
		   get_opt.c \
		   get_args.c \
		   sort.c \
		   elem.c \
		   free.c \
		   ft_ls.c \
		   print.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

NAME = ft_ls
CC = gcc
LIBFT = libft/libft.a
CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(SRC) -Iincludes -o $(NAME) libft/libft.a

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -c $< -Iincludes -o $@

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJ_PATH)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all re clean fclean
