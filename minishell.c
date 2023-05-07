/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:50 by josanton          #+#    #+#             */
/*   Updated: 2023/05/06 21:36:09 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changes Ctrl+C to \n
void	sig_handler(int n)
{
	(void)n;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
}

bool	is_builtin(char **command, t_token *token_lst)
{
	bool	ret;

	ret = true;
	if (!ft_strcmp(command[0], "env"))
		env(token_lst);
	else if (!ft_strcmp(command[0], "export"))
		export(command, token_lst);
	else if (!ft_strcmp(command[0], "unset"))
		unset(command);
	else if (!ft_strcmp(command[0], "cd"))
		cd(command);
	else if (!ft_strcmp(command[0], "pwd"))
		pwd(command, token_lst);
	else if (!ft_strcmp(command[0], "echo"))
		echo(command, token_lst);
	else if (!ft_strcmp(command[0], "exit"))
		exit(0);
	else
		ret = false;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ignore_signal();
	store_env(envp);
	while (1)
	{
		get_input();
		if (_input()->command[0] != '\0')
		{
			analyze_and_parse(_input()->command);
			free_matrix(_input()->token_matrix);
		}
		free(_input()->command);
	}
	return (0);
}
