/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:40 by josanton          #+#    #+#             */
/*   Updated: 2023/06/10 22:49:00 by salatiel         ###   ########.fr       */
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
	char	**path_split;

	if (access(cmd, F_OK) == 0)
	{
		command = ft_strdup(cmd);
		return (command);
	}
	path_split = ft_split(info()->path, ':');
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		command = ft_strdup(cmd);
		free_path(path_split);
		return (command);
	}
	i = -1;
	while (path_split && path_split[++i])
	{
		command = ft_strjoin_sep(path_split[i], cmd, '/');
		if (access(command, F_OK) == 0)
		{
			free_path(path_split);
			return (command);
		}
		free(command);
	}
	if (path_split)
		free_path(path_split);
	if (ft_strcmp(cmd, "exit"))
		cmd_not_found(cmd);
	return (NULL);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	cmd_not_found(char *cmd)
{
	printf("Command '%s' not found\n", cmd);
	info()->error_code = 127;
	info()->cmd_not_found = true;
	info()->cmd_nr++;
}

void	execute(t_token *token_lst, char **cmd, int fd_in, int fd_out)
{
	char	*command;
	int		pid;
	bool	blt_in;

	blt_in = is_builtin(cmd, token_lst, fd_in, fd_out);
	if (!blt_in)
	{
		command = check_executable(cmd[0]);
		if (!command)
		{
			free(command);
			free_matrix(cmd);
			return ;
		}
		pid = fork();
		info()->exit_pid = pid;
		if (pid == -1)
			return ;
		else if (pid == 0)
		{
			dup_info(token_lst, fd_in, fd_out);
			run(cmd, command);
			exit(info()->error_code);
		}
		free(command);
	}
	free_matrix(cmd);
}
