# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 13:06:11 by yroussea          #+#    #+#              #
#    Updated: 2024/01/16 10:18:18 by yroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = \
	ft_char.c \
	ft_mem.c \
	ft_str.c \
	ft_print.c \
	ft_stk.c \
	ft_lst.c \
	ft_gnl.c \
	ft_type.c

OBJS = $(SRCS:.c=.o)

PROJECT = libft
NAME = libft.a
DIR_NAME = libf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m
bold := $(shell tput bold)
notbold := $(shell tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\r%b" "$(COLOUR_GREEN)Compiling $(PROJECT)$(NO_COLOR)";
	@ar rcs $(NAME) $(OBJS)
	@echo -n "\033[2K";
	@printf "\r%b" "🌟 $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

%.o: %.c
	@echo -n "\033[2K";
	@printf "\r%b" "$(COLOUR_YELLOW)$(bold)[🔥 Compiling 🔥]$(notbold)$(COLOUR_YELLOW) $(DIR_NAME)/$(^)$(NO_COLOR)";
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@printf "\r%b" "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo -n "\033[2K"
	@printf "\r%b" "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
