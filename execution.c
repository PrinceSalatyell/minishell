/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:40 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 13:38:12 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(char **cmd, char *command)
{
	int	res;

	res = execve(command, cmd, NULL);
	if (res == -1)
		exit(1);
}

char	*check_executable(char *cmd)
{
	int		i;
	char	*command;

	i = -1;
	while (info()->path[++i])
	{
		command = ft_strjoin_sep(info()->path[i], cmd, \
		'/');
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	printf("Command '%s' not found\n", cmd);
	return (NULL);
}

// flag -> red_in = 0 | red_out - 1
void	execute_redirection(char **cmd, int fd_in, int fd_out)
{
	char	*command;
	int	pid;

	command = check_executable(cmd[0]);
	if (!command)
	{
		free(command);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (info()->in_flag == TRUE)
			dup2(fd_in, STDIN_FILENO);
		if (info()->out_flag == TRUE)
			dup2(fd_out, STDOUT_FILENO);
		run(cmd, command);
	}
	free(command);
}

void	execute(t_token *token_lst, char **cmd, char *command)
{
	int	j;

	j = -1;
	if (info()->cmd_nr == 0 && !token_lst->next)
		run(cmd, command);
	else
	{
		if (info()->cmd_nr != 0)
			dup2(info()->fd[info()->cmd_nr - 1][0], STDIN_FILENO);
		if (token_lst->next)
			dup2(info()->fd[info()->cmd_nr][1], STDOUT_FILENO);
		while (++j < info()->nr_pipe)
		{
			close(info()->fd[j][0]);
			close(info()->fd[j][1]);
		}
		run(cmd, command);
	}
}

// fd[0] - read
// fd[1] - write
void	execute_simple_cmd(t_token *token_lst, char **cmd)
{
	char	*command;
	int		pid;
	bool	blt_in;

	blt_in = is_builtin(cmd, token_lst);
	if (!blt_in)
	{
		command = check_executable(cmd[0]);
		if (!command)
		{
			free(command);
			return ;
		}
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
				execute(token_lst, cmd, command);
		free(command);
	}
}
