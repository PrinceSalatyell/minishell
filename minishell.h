/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:51:46 by josanton          #+#    #+#             */
/*   Updated: 2023/05/12 16:53:17 by salatiel         ###   ########.fr       */
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
	char	**new_token_matrix;
	int		index;
	int		qt_flag;
}	t_input;

typedef struct s_info
{
	char	**path;
	int	cmd_nr;
	int	nr_pipe;
	int	file_flag;
	int	**fd_pipe;
	bool	fd_red;
	bool	in_flag;
	bool	out_flag;
	t_dict	*env;
	char	*home;
	bool	home_set;
	int		shlvl;
}	t_info;

// minishell.c
void	sig_handler(int n);
void	ignore_signal(void);
bool	is_builtin(char **command, t_token *token_lst, int fd_in, int fd_out);

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
int		get_command_len(int i);

// get_token.c
int		token_len(char *str, int i);
int		matrix_len(char *str);
int	separate_pipe(char *str, int *i, int len);
int		qt_len(char *str, int i);
void	free_matrix(char **matrix);

// parser.c
void	parse_commands(t_token *token_lst);
void	check_command_type(t_token *token_lst, char **cmd);
void	parse_redirection(t_token *token_lst, char **cmd);
int	get_fd_out(char **cmd_red);
int	get_fd_in(char **cmd_red);
void	heredocs();

// execution.c
void	run(char **cmd, char *command);
char	*check_executable(char	*cmd);
void	execute(t_token *token_lst, char **cmd, char *command);
void	execute_simple_cmd(t_token *token_lst, char **cmd);
void	execute_redirection(t_token *token_lst, char **cmd, int fd_in, int fd_out);

// expansions.c
void	cpy_var_value(char *new_str, char *old_str, int *i, int *k);
char	*replace_var(char *old_str, int len, int i, int k);
char	*expand_var(char *old_str);
char	**handle_expansion(char **token_matrix);

// expd_utils.c
int get_expanded_len(char *old_str, int i);
char    *get_var_value(char *var_key);
char	*get_var_key(char *str, int i);
bool	is_expansion(char *str);

// utils.c
int		quotes_end(char *str, int i);
char	*ft_strjoin_nl(char *s1, char *s2);
void	cpy_command(t_token **token_lst, int i);
void	cpy_operator(t_token **token_lst, int i);
void	free_fd(int	**fd);

// utils2.c
void	dup_bult_in(t_token *token_lst, int fd_in, int fd_out);
char    **get_cmd_red_matrix(char **cmd_red, int j);
int get_cmd_red_len(char **cmd_red);
int	**get_pipe_fd(void);
bool	check_pipe(t_token *token_lst);

// red_utils.c
char	*get_dir_path(char *cmd);
int	open_file(char *file, int flag);
int	check_if_invalid(char **cmd);

// struct_utils.c
void	add_back(t_token **token_list, t_token *new);
t_token	*lst_last(t_token *token_lst);
t_token	*new_token(char *type, int cmd_len, int i);
void	free_list(t_token **token);
int		separate_pipe(char *str, int *i, int len);

// dict_utils.c
t_dict	*ft_dictnew(char *key, char *value);
void	ft_dictadd_back(t_dict **dict, t_dict *new);
int		ft_dictsize(t_dict *dict);
void	ft_dictdel(t_dict **dict, char *key);
void	ft_dictclear(t_dict **dict);

// init.c
t_input	*_input(void);
t_info	*info(void);

// exec_utils.c
int		size_of_env(void);
char	**create_env_list(void);
void	free_env_list(char **env_list);

// BUILT-INS DIRECTORY

// env.c
void	store_env(char **envp);
void	env(t_token *token_lst, int fd_in, int fd_out);
char	*get_value(char *env_line);
char	*get_key(char *env_line);

//export.c
void	print_export(int size, char *last_printed);
void	export(char **command, t_token *token_lst, int fd_in, int fd_out);
void	add_to_env(char **comand, t_token *token_lst);
void	print_it(char *key, char *value);
bool	search_for_variable(char *key);

// unset.c
void	unset(char **command, t_token *token_lst);

// cd.c
void	cd(char **command, t_token *token_lst);
char	*get_home(void);
void	change_directory(char *path, t_token *token_lst);
void	change_pwd(char *to_change, char *new_value);
char	*get_old_pwd(void);

// pwd.c
void	pwd(char **command, t_token *token_lst, int fd_in, int fd_out);

// echo.c
void	echo(char **command, t_token *token_lst, int fd_in, int fd_out);

#endif