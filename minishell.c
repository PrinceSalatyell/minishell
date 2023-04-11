/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:50 by josanton          #+#    #+#             */
/*   Updated: 2023/04/02 17:58:46 by josanton         ###   ########.fr       */
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

bool	is_builtin(char *command)
{
	bool	ret;

	ret = true;
	if (!ft_strcmp(command, "env"))
		env();
	else if (!ft_strcmp(command, "export"))
		export(0, NULL);
	// else if (!ft_strcmp(command, "echo"))
	// 	echo();
	// else if (!ft_strcmp(command, "pwd"))
	// 	pwd();
	// else if (!ft_strcmp(command, "cd"))
	// 	cd();
	// else if (!ft_strcmp(command, "unset"))
	// 	unset();
	else if (!ft_strcmp(command, "exit"))
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
