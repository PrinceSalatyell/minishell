/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:51:46 by josanton          #+#    #+#             */
/*   Updated: 2023/03/24 20:51:52 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

// COLORS

# define BLUE "\033[1;36m"
# define YELLOW "\033[0;33m"
# define RED "\033[1;31m"
# define COLOUR_END "\033[0m"

typedef struct s_token
{
	char			*value;
	char			*type;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	char	*command;
	char	**token_matrix;
	int		index;
	int		qt_flag;
}	t_input;

typedef struct s_info
{
	char	**path;
}	t_info;

// check_str.c
int		check_qt_marks(char *str, int i);
void	check_if_complete(char *str);
int		check_pipe_done(char *str, int i);

// get_input.c
void	get_input(void);
void	loop_promt(char *str, int qt);

// str_parse.c
void	analyze_and_parse(char *str);
void	tokenizer(char *str, int i);
void	get_token_list(t_token **token_lst, int i);

// get_token.c
void	free_token(void);
int		token_len(char *str, int i);
int		matrix_len(char *str);
int		qt_len(char *str, int i);

// utils.c
int		quotes_end(char *str, int i);
char	*ft_strjoin_nl(char *s1, char *s2);
void	add_back(t_token **token_list, t_token *new);
t_token	*lst_last(t_token *token_lst);
t_token	*new_token(char *value, char *type);
void	free_list(t_token **token);

// init.c
t_input	*_input(void);
t_token	*token_node(void);

// minishell.c
void	sig_handler(int n);
void	ignore_signal(void);

// execution.c
void	execute(void);

// init.c
t_input	*_input(void);
t_info	*info(void);

#endif