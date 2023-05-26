# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 10:58:18 by frmonfre          #+#    #+#              #
#    Updated: 2023/05/26 10:51:16 by frmonfre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	pipex.c str_utils1.c str_utils2.c free_error.c execution.c

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
	@echo "______ _                 "
	@echo "| ___ (_)                "
	@echo "| |_/ /_ _ __   _____  __"
	@echo "|  __/| | '_ \ / _ \ \/ /"
	@echo "| |   | | |_) |  __/>  < "
	@echo "\\_|   |_| .__/ \\___/_/\\_\\"
	@echo "        | |              "
	@echo "        |_|              "

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
