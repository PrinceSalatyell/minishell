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

int	**get_pipes(void)
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
	int	pid;
	int	**fd;
	int	j;
	
	fd = get_pipes();
	while (token_lst)
	{
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			command = check_executable(token_lst->value[0]);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
			{
				if (i != 0)
					dup2(fd[i-1][0], STDIN_FILENO);
				if (token_lst->next)
					dup2(fd[i][1], STDOUT_FILENO);
				j = 0;	
				while (j < info()->nr_pipe)
				{
					close(fd[j][0]);
					close(fd[j][1]);
					j++;
				}
				run(token_lst, command);
			}
			free(command);
			i++;
		}
		token_lst = token_lst->next;
	}
	j = 0;
	while (j < info()->nr_pipe)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	wait(NULL);
	free_fd(fd);
	// command = check_executable(token_lst->value[0]);
	// pid = fork();
	// if (pid == -1)
	// 	return ;
	// if (pid == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	//printf("value -> %s\n", token_lst->value[0]);
	// 	run(token_lst, command);
	// }
	// free(command);
	// token_lst = token_lst->next;
	// token_lst = token_lst->next;
	// command = check_executable(token_lst->value[0]);
	// pid2 = fork();
	// if (pid2 == -1)
	// 	return ;
	// if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);	
	// 	//printf("value -> %s\n", token_lst->value[0]);
	// 	run(token_lst, command);
	// }
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
