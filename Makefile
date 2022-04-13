# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frrusso <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:22:00 by frrusso           #+#    #+#              #
#    Updated: 2022/03/31 12:22:04 by frrusso          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
NAME	= pipex
LIBFT	= libft/libft.a
SRCS	= ${addprefix srcs/, main.c pipex.c}
OBJS	= ${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
	${MAKE} -C libft
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

all:${NAME}

clean:
	${MAKE} clean -C libft
	${RM} ${OBJS}

fclean:clean
	${MAKE} fclean -C libft
	${RM} ${NAME}

re:fclean all

debug:${OBJS}
	${MAKE} -C libft
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} \
	&& clear && ./pipex files/infile "ls -l" "wc -l" files/outfile

.PHONY: all clean fclean re debug
