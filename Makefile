# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 12:45:20 by josanton          #+#    #+#              #
#    Updated: 2023/06/23 13:40:16 by salatiel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION VARS

SRCS	=	minishell.c					\
			parsing/get_input.c			\
			parsing/check_str.c			\
			parsing/lexer.c				\
			parsing/get_token.c			\
			parsing/parser.c			\
			utils/red_utils.c			\
			execution/execution.c		\
			utils/exec_utils.c			\
			parsing/expansions.c		\
			utils/expd_utils.c			\
			utils/utils.c				\
			utils/utils2.c				\
			utils/struct_utils.c		\
			utils/dict_utils.c			\
			tools/init.c				\
			tools/heredoc.c				\
			builtins/env.c				\
			builtins/export.c			\
			builtins/unset.c			\
			builtins/cd.c				\
			builtins/pwd.c				\
			builtins/echo.c				\
			builtins/exit.c				\
			builtins/exit_minishell.c

OBJS	=	${SRCS:%.c=${DIR_OBJ}%.o}

NAME	=	minishell

#DIRECTORIES

LIBFT_DIR	=	libft/

DIR_OBJ = objs/

#GCC & FLAGS

CC	=	clang

42FLAGS	=	-Wall -Werror -Wextra -g

EXTRA_FLAGS =	-Ilibft/ -L${LIBFT_DIR} -lft -lreadline -g -fsanitize=address

GCC	=	${CC} ${42FLAGS}

#CLEAN

RM	=	rm -f

#COLORS

COLOUR_GREEN=\033[7;1;32m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[7;1;33m

# ===============Implement================= R U L E S ================================

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
