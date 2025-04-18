# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 14:11:54 by fvargas           #+#    #+#              #
#    Updated: 2025/04/16 12:04:15 by fvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philo
CC = 		cc
CFLAGS = 	-Wall -Wextra -Werror -g
HDRS :=		src/philosophers.h
SRCS =		src/actions.c src/checker.c src/create.c src/error.c src/log.c \
			src/main.c src/monitor.c src/mutex.c src/process.c src/time.c src/util.c

OBJS = 		$(SRCS:.c=.o)

RM	=		rm -rf

${NAME}:$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}
		
re: fclean all

$(OBJS): $(HDRS)