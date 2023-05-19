# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 10:58:18 by frmonfre          #+#    #+#              #
#    Updated: 2023/05/19 11:03:14 by frmonfre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	pipex.c concatenate.c ft_split.c free.c exe_managment.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	pipex

CC	=	gcc

CFLAG	=	-w -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)
	norminette

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

push:
	make fclean
	git add .
	git commit -m "Makefile auto-commit"
	git push

.PHONY: re fclean all clean push
