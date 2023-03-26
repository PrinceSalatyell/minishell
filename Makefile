# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josanton <josanton@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 12:45:20 by josanton          #+#    #+#              #
#    Updated: 2023/03/26 12:03:00 by josanton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION VARS

SRCS	=	minishell.c	\
			parser.c	\
			init.c		\
			utils.c		\
			get_input.c	\
			check_str.c	\
			get_token.c \
			execution.c

OBJS	=	${SRCS:%.c=${DIR_OBJ}%.o}

NAME	=	minishell

#DIRECTORIES

LIBFT_DIR	=	libft/

DIR_OBJ = objs/

#GCC & FLAGS

CC	=	clang

42FLAGS	=	-Wall -Werror -Wextra -g

EXTRA_FLAGS =	-Ilibft/ -L${LIBFT_DIR} -lft -lreadline -fsanitize=leak

GCC	=	${CC} ${42FLAGS}

#CLEAN

RM	=	rm -f

#COLORS

COLOUR_GREEN=\033[7;1;32m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[7;1;33m

# ================================ R U L E S ================================

all:	${NAME}

${NAME}:	${OBJS} libft/libft.a
	@${GCC} -o ${NAME} ${OBJS} ${EXTRA_FLAGS}
	@echo "${COLOUR_GREEN} >>> Minishell OK <<< ${COLOUR_END}"

${DIR_OBJ}%.o:%.c
	@git submodule update --init --recursive
	@mkdir -p ${dir $@}
	@${CC} ${42FLAGS} -c $< -o $@

libft/libft.a:
	@make -s -C ${LIBFT_DIR}

clean:
	@${MAKE} -s clean -C ${LIBFT_DIR}
	@${RM} -r ${DIR_OBJ}
	@echo "${COLOUR_YELLOW} >>> OBJS CLEANED <<< ${COLOUR_END}"

fclean:		clean
	@${MAKE} -s fclean -C ${LIBFT_DIR}
	@${RM} ${NAME}
	@echo "${COLOUR_YELLOW} >>> ALL CLEANED <<< ${COLOUR_END}"

re:	fclean all

.PHONY:	all clean fclean re libft