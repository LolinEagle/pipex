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
FLAGS	= -Wall -Wextra -Werror
NAME	= pipex
LIBFT	= libft/libft.a
SRCS	= ${addprefix srcs/, ft_pipex.c pipex.c struct.c ft_main.c main.c}
OBJS	= ${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
	${MAKE} -C libft
	${CC} ${FLAGS} ${OBJS} ${LIBFT} -o ${NAME}

all:${NAME}

clean:
	${MAKE} clean -C libft
	${RM} ${OBJS}

fclean:clean
	${MAKE} fclean -C libft
	${RM} ${NAME}

re:fclean all

.PHONY: all clean fclean re
