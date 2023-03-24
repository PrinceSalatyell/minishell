/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:40 by josanton          #+#    #+#             */
/*   Updated: 2023/03/24 20:51:10 by salatiel         ###   ########.fr       */
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
			execve(command, _input()->token_matrix, NULL);
		wait(NULL);
		free(command);
	}
	else
		printf("Command Not Found\n");
	if (command)
		free(command);
}
