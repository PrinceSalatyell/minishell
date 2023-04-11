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

void	execute_redirection(char **cmd, int fd)
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
		dup2(fd, STDOUT_FILENO);
		close(fd);
		run(cmd, command);
	}
	free(command);
}

void	execute(t_token *token_lst, char **cmd, char *command, int **fd)
{
	int	j;

	j = -1;
	if (info()->cmd_nr == 0 && !token_lst->next)
		run(cmd, command);
	else
	{
		if (info()->cmd_nr != 0)
			dup2(fd[info()->cmd_nr - 1][0], STDIN_FILENO);
		if (token_lst->next)
			dup2(fd[info()->cmd_nr][1], STDOUT_FILENO);
		while (++j < info()->nr_pipe)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		run(cmd, command);
	}
}

// fd[0] - read
// fd[1] - write
void	execute_simple_cmd(t_token *token_lst, char **cmd, int **fd)
{
	char	*command;
	int		pid;
	int	j;

	command = check_executable(cmd[0]);
	if (!command)
	{
		free(command);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	j = -1;
	if (pid == 0)
			execute(token_lst, cmd, command, fd);
	free(command);
}
