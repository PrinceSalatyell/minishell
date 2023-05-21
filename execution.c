/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:40 by josanton          #+#    #+#             */
/*   Updated: 2023/05/21 03:06:38 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(char **cmd, char *command)
{
	int		res;
	char	**env_list;

	env_list = create_env_list();
	res = execve(command, cmd, env_list);
	free_env_list(env_list);
	signal(SIGINT, SIG_DFL);
	if (res == -1)
	{
		if (access(command, F_OK) == 0)
			printf("'%s': Permission denied\n", cmd[0]);
		else
			printf("'%s': File does not exist\n", cmd[0]);
		exit(errno);
	}
}

char	*check_executable(char *cmd)
{
	int		i;
	char	*command;

	if (cmd[0] == '.' && cmd[1] == '/')
	{
		command = ft_strdup(cmd);
		return (command);
	}
	i = -1;
	while (info()->path[++i])
	{
		command = ft_strjoin_sep(info()->path[i], cmd, \
		'/');
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	if (strcmp(cmd, "exit"))
	{
		printf("Command '%s' not found\n", cmd);
		info()->error_code = 127;
	}
	return (NULL);
}

void	execute(t_token *token_lst, char **cmd, int fd_in, int fd_out)
{
	char	*command;
	int		pid;
	bool	blt_in;
	//int		status;

	blt_in = is_builtin(cmd, token_lst, fd_in, fd_out);
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
		else if (pid == 0)
		{
			dup_info(token_lst, fd_in, fd_out);
			run(cmd, command);
			exit(info()->error_code);
		}
		//else
		//{
		//	waitpid(pid, &status, 0);
		//	info()->error_code = WEXITSTATUS(status);
		//}
		free(command);
	}
}
