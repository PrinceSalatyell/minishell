/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:51:47 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/06 21:45:39 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(char **command, t_token *token_lst)
{
	char	*path;
	pid_t	pid;

	if (command[1] && command[1][0] == '-' && command[1][1])
		printf("minishell: pwd: -%c: invalid option\npwd: usage: pwd [no options]\n", command[1][1]);
	else
	{
		pid = fork();
		if (pid < 0)
			perror("minishell");
		else if (pid == 0)
		{
			dup_bult_in(token_lst);
			path = getcwd(NULL, 0);
			if (path != NULL)
			{
				printf("%s\n", path);
				free(path);
			}
			else
				perror("minishell");
			exit(0);
		}
		else
			wait(NULL);
	}
}
