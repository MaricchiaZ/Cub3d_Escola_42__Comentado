# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 15:53:00 by gissao-m          #+#    #+#              #
#    Updated: 2023/04/28 15:46:23 by gissao-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = vector.c vector2.c

HEADERS    = ../vector.h

OBJS    = ${SRCS:.c=.o}

NAME    = libvector.a

RM    = rm -f

.c.o:
	@cc -Wall -Wextra -Werror -g -c $< -I ${HEADERS} -o ${<:.c=.o}
	
all: ${NAME}

${NAME}:    ${OBJS}
	@ar -rcs ${NAME} ${OBJS}

clean:
	@${RM} ${OBJS}

fclean:    clean
	@${RM} ${NAME}

re: fclean all

.PHONY:    all clean fclean re
