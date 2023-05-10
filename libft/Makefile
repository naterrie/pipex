# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 14:37:56 by naterrie          #+#    #+#              #
#    Updated: 2023/05/10 17:17:26 by naterrie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BONUS	=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

SRCS	=	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

OBJS		= $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

OBJS_BONUS	= $(addprefix $(DIR_OBJS)/, $(BONUS:.c=.o)) \
				$(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

HEADER = libft.h
DIR_SRCS = src
FLAGS	= -Wall -Wextra -Werror
DIR_OBJS = .objs
NAME	= libft.a

BLEU := \033[36m
PURPLE := \033[35m
GREEN := \033[32m
RED := \033[31m
RESET := \033[0m
ERASE := \033[2K\033[1A\r

all:	$(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	echo "$(GREEN)⏳ Making Bonus $(NAME)"
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	printf "$(ERASE)"
	echo "$(GREEN)✅ Libft Bonus compilated !"

$(NAME): $(DIR_OBJS) $(OBJS)
	echo "$(GREEN)⏳ Making libft"
	ar rcs $(NAME) $(OBJS)
	printf "$(ERASE)"
	echo "$(GREEN)✅ libft compilated !"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(HEADER) Makefile
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@
	printf "$(ERASE)"

$(DIR_OBJS):
	mkdir -p $@

clean:
	rm -rf .objs
	echo "$(PURPLE)🧹Removing libft.o files !"

fclean:	clean
	rm -f $(NAME)
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
re:	fclean $(NAME)

.PHONY:	all clean fclean re bonus

.SILENT:

