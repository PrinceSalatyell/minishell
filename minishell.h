/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:51:46 by josanton          #+#    #+#             */
/*   Updated: 2023/04/01 19:58:53 by salatiel         ###   ########.fr       */
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

# define FALSE 0
# define TRUE 1

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_token
{
	char			**value;
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
	int	cmd_nr;
	int	nr_pipe;
	int	file_flag;
	bool	in_flag;
	bool	out_flag;
	t_dict	*env;
}	t_info;

// minishell.c
void	sig_handler(int n);
void	ignore_signal(void);
bool	is_builtin(char *command);

// get_input.c
void	get_input(void);
void	loop_promt(char *str, int qt);

// check_str.c
int		check_qt_marks(char *str, int i);
void	check_if_complete(char *str);
int		check_pipe_done(char *str, int i);

// lexer.c
void	analyze_and_parse(char *str);
void	tokenizer(char *str, int i);
void	copy_token(char *str, int i, int tk_len, int index);
void	get_token_list(t_token **token_lst, int i);
int	get_command_len(int i);

// get_token.c
int		token_len(char *str, int i);
int		matrix_len(char *str);
int	separate_pipe(char *str, int *i, int len);
int		qt_len(char *str, int i);
void	free_matrix(char **matrix);

// parser.c
void	parse_commands(t_token *token_lst);
void	check_command_type(t_token *token_lst, char **cmd, int **fd);
void	parse_redirection(char **cmd);
int	get_fd_out(char **cmd_red);
int	get_fd_in(char **cmd_red);
char	*get_dir_path(char *cmd);
int	open_file(char *file, int flag);

// redirections.c
void	heredocs();

// execution.c
void	run(char **cmd, char *command);
char	*check_executable(char	*cmd);
void	execute(t_token *token_lst, char **cmd, char *command, int **fd);
void	execute_simple_cmd(t_token *token_lst, char **cmd, int **fd);
void	execute_redirection(char **cmd, int fd_in, int fd_out);

// utils.c
int		quotes_end(char *str, int i);
char	*ft_strjoin_nl(char *s1, char *s2);
void	cpy_command(t_token **token_lst, int i);
void	cpy_operator(t_token **token_lst, int i);
void	free_fd(int	**fd);
t_token	*rm_quotes(t_token *token_lst, char *str);

// utils2.c
char    **get_cmd_red_matrix(char **cmd_red, int j);
int get_cmd_red_len(char **cmd_red);
int	**get_pipe_fd(void);

// struct_utils.c
void	add_back(t_token **token_list, t_token *new);
t_token	*lst_last(t_token *token_lst);
t_token	*new_token(char *type, int cmd_len, int i);
void	free_list(t_token **token);
int	separate_pipe(char *str, int *i, int len);

// dict_utils.c
t_dict	*ft_dictnew(char *key, char *value);
void	ft_dictadd_back(t_dict **dict, t_dict *new);
int		ft_dictsize(t_dict *dict);
void	ft_dictdellast(t_dict **dict);
void	ft_dictclear(t_dict **dict);

// init.c
t_input	*_input(void);
t_info	*info(void);

// BUILT-INS DIRECTORY

// env.c
void	store_env(char **envp);
void	env(void);
char	*get_value(char *env_line);
char	*get_key(char *env_line);

//export.c
void	export(int size, char *last_printed);

#endif