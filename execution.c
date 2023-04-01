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

void	run(t_token *token_lst, char *command)
{
	int	res;

	res = execve(command, token_lst->value, NULL);
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
	return (NULL);
}

int	find_command(t_token *token_lst)
{
	char	*command;
	int	i;

	// if (!token_lst->value[0])
	// 	return (0);
	i = 0;
	while (token_lst)
	{
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			command = check_executable(token_lst->value[0]); 
			if (!command)
			{
				printf("Command '%s' not found\n", token_lst->value[0]);
				free(command);
				return (0);
			}
			free(command);
		}
		token_lst = token_lst->next;
		i++;
	}
	return (1);
}

int	**get_pipe_fd(void)
{
	int	**fd;
	int	i;

	fd = malloc(sizeof(int*) * info()->nr_pipe);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < info()->nr_pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i < info()->nr_pipe)
	{
		if (pipe(fd[i]) == -1)
			return (NULL);
		i++;
	}
	return (fd);
}

// fd[0] - read
// fd[1] - write
void	execute_multiple(t_token *token_lst, int i)
{
	char	*command;
	pid_t	pid;
	int	**fd;
	int	j;
	
	fd = get_pipe_fd();
	pid = 1;
	while (token_lst)
	{
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			command = check_executable(token_lst->value[0]);
			pid = fork();
			if (pid == -1)
			{
				printf("Error forking process\n");
				exit(1);
			}
			if (pid == 0)
			{
				if (i != 0)
					dup2(fd[i-1][0], STDIN_FILENO);
				if (token_lst->next)
					dup2(fd[i][1], STDOUT_FILENO);
				j = -1;	
				while (++j < info()->nr_pipe)
				{
					close(fd[j][0]);
					close(fd[j][1]);
				}
				run(token_lst, command);
			}
			free(command);
			i++;
		}
		token_lst = token_lst->next;
	}
	j = -1;
	while (++j < info()->nr_pipe)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	free_fd(fd);
	j = -1;
	while (++j < info()->nr_pipe + 1)
		wait(NULL);
}

void	execute(t_token *token_lst)
{
	char	*command;
	int		pid;

	if (!find_command(token_lst))
		return ;
	if (info()->nr_pipe == 0)
	{
		command = check_executable(token_lst->value[0]);
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			run(token_lst, command);
		wait(NULL);
		free(command);
	}
	else
		execute_multiple(token_lst, 0);
}
