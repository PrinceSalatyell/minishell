/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:50 by josanton          #+#    #+#             */
/*   Updated: 2023/06/18 20:34:32 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changes Ctrl+C to \n
void	sig_handler(int n)
{
	pid_t	pid;
	int		status;

	(void)n;
	pid = waitpid(-1, &status, 0);
	if (pid == -1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void	ignore_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

bool	is_builtin(char **command, t_token *token_lst, int fd_in, int fd_out)
{
	bool	ret;

	ret = true;
	if (!ft_strcmp(command[0], "env"))
		env(token_lst, fd_in, fd_out);
	else if (!ft_strcmp(command[0], "export"))
		export(command, token_lst, fd_in, fd_out);
	else if (!ft_strcmp(command[0], "unset"))
		unset(command, token_lst);
	else if (!ft_strcmp(command[0], "cd"))
		cd(command, token_lst);
	else if (!ft_strcmp(command[0], "pwd"))
		pwd(command, token_lst, fd_in, fd_out);
	else if (!ft_strcmp(command[0], "echo"))
		echo(command, token_lst, fd_in, fd_out);
	else
		ret = false;
	info()->builtin = ret;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ignore_signal();
	store_env(envp);
	info()->error_code = 0;
	while (1)
	{
		get_input();
		if (_input()->command[0] != '\0' && !info()->exit_flag)
		{
			analyze_and_parse(_input()->command);
			free_matrix(_input()->new_token_matrix);
			free_matrix(_input()->token_matrix);
		}
		free(_input()->command);
	}
	return (0);
}
