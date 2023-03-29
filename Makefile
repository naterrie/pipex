# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 13:19:29 by naterrie          #+#    #+#              #
#    Updated: 2023/03/29 03:42:27 by naterrie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME =	pipex
HEADERS = pipex.h
CFLAGS = -Wall -Werror -Wextra

DIR_SRCS := src
DIR_OBJS := .objs
DIR_LIBFT := libft
LST_LIBFT := libft.a

OBJS =	$(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))
LIBFT = $(addprefix $(DIR_LIBFT)/, $(LST_LIBFT))


BLEU := \033[36m
PURPLE := \033[35m
GREEN := \033[32m
RED := \033[31m
RESET := \033[0m
ERASE := \033[2K\033[1A\r

SRCS =	pipex.c \
		pars.c

all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS) ${LIBFT}
	gcc $(CFLAGS) -o $(NAME) $(OBJS) ${LIBFT}
	echo "$(GREEN)✅ $(NAME) compilated !"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(HEADERS)
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@ -I.
	sleep 0.05
	printf "$(ERASE)"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT):
	echo "$(GREEN)⏳ Making LIBFT"
	make -C libft
	printf "$(ERASE)"
	echo "$(GREEN)✅ LIBFT compilated !"

clean:
	echo "$(PURPLE)🧹Removing .o files !"
	rm -rf $(DIR_OBJS)
	make -C libft clean

fclean: clean
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
	rm -f $(NAME)
	make -C libft fclean

re: fclean $(NAME)

.PHONY: clean fclean re all

.SILENT:
