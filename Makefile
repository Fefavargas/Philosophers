# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 14:11:54 by fvargas           #+#    #+#              #
#    Updated: 2025/02/24 14:13:36 by fefa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philosophers
CC = 		cc -g
CFLAGS = 	-Wall -Wextra -Werror -g
HDRS :=		src/philosophers.h
SRCS =		src/actions.c src/checker.c src/create.c src/error.c src/log.c \
			src/main.c src/monitor.c src/mutex.c src/process.c src/time.c src/util.c

OBJS = 		$(SRCS:.c =.o)

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