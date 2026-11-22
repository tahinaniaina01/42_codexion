# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/26 16:35:28 by trakotos          #+#    #+#              #
#    Updated: 2026/11/22 14:32:12 by trakotos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf
SRCS = \
	src/cleanup.c \
	src/coder.c \
	src/codexion.c \
	src/dongle.c \
	src/heap_ops.c \
	src/init.c \
	src/init_coders.c \
	src/init_dongles.c \
	src/init_scheduling.c \
	src/log.c \
	src/main.c \
	src/monitor.c \
	src/parse.c \
	src/scheduler.c \
	src/time_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
