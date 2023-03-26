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

char	*check_executable(void)
{
	int		i;
	char	*ret;
	char	*command;

	i = -1;
	ret = NULL;
	while (info()->path[++i])
	{
		command = ft_strjoin_sep(info()->path[i], _input()->token_matrix[0], \
		'/');
		if (access(command, F_OK) == 0)
			ret = command;
	}
	return (ret);
}

void	run(char *command)
{
	int	res;

	res = execve(command, _input()->token_matrix, NULL);
	if (res == -1)
		exit(1);
}

void	execute(void)
{
	char	*command;
	int		pid;

	command = check_executable();
	if (command)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			run(command);
		wait(NULL);
		free(command);
	}
	else
		printf("Command Not Found\n");
	if (command)
		free(command);
}
