# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 18:25:23 by ffoissey          #+#    #+#              #
#    Updated: 2018/11/29 17:37:15 by ffoissey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FILE = fillit fill_tets backtrack tet_extra
LIBFT = libft/libft.a
SRCS = $(patsubst %,ft_%.c,$(FILE))
OBJS = $(patsubst %,ft_%.o,$(FILE))
INCLUDES = -I libft/includes -I libft/includes/get_next_line -I libft/includes/ft_printf 
HEAD = fillit.h
CFLAGS = -Wall -Werror -Wextra
CC = clang

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEAD)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) -o $@

$(LIBFT):
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $? $(INCLUDES)

clean:
	rm -f $(OBJS) && make -C libft clean

fclean: clean
	rm -f $(NAME) && make -C libft fclean

re: fclean all

.PHONY: clean fclean re all
