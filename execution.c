/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:40 by josanton          #+#    #+#             */
/*   Updated: 2023/03/23 23:52:22 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_executable(char *cmd)
{
	int		i;
	bool	ret;
	char	*command;

	i = -1;
	ret = false;
	while (info()->path[++i])
	{
		command = ft_strjoin_sep(info()->path[i], cmd, '/');
		if (access(command, F_OK) == 0)
			ret = true;
		free(command);
	}
	return (ret);
}

void	execute(char *cmd)
{
	if (check_executable(cmd))
		printf("This program exists\n");
	else
		printf("Command Not Found\n");
}
