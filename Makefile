# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 14:11:54 by fvargas           #+#    #+#              #
#    Updated: 2025/02/03 14:51:27 by fvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philosophers
CC = 		cc
CFLAGS = 	-Wall -Wextra -Werror -g
HDRS :=		src/philosophers.h
SRCS =		src/checker.c src/create.c src/main.c src/util.c

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