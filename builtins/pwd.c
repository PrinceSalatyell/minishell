/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:51:47 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/21 04:01:50 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(char **command, t_token *token_lst, int fd_in, int fd_out)
{
	pid_t	pid;

	if (command[1] && command[1][0] == '-' && command[1][1])
	{
		printf("minishell: pwd: -%c: invalid option\n", command[1][1]);
		info()->error_code = 2;
	}
	else
	{
		pid = fork();
		if (pid < 0)
			perror("minishell");
		else if (pid == 0)
			navigate(token_lst, fd_in, fd_out);
		else
			wait(NULL);
		info()->error_code = 0;
	}
}

void	navigate(t_token *token_lst, int fd_in, int fd_out)
{
	char	*path;

	dup_info(token_lst, fd_in, fd_out);
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