/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:22:24 by salatiel          #+#    #+#             */
/*   Updated: 2023/06/10 20:14:48 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_newline(char **command, int *i, bool *no_newline)
{
	int	j;

	while (command[*i] && command[*i][0] == '-')
	{
		j = 1;
		while (command[*i][j] == 'n')
		{
			*no_newline = true;
			j++;
		}
		if (command[*i][j] != '\0')
			break ;
		(*i)++;
	}
}

void	echo_output(char **command, int i, bool no_newline)
{
	bool	first_word;

	first_word = true;
	while (command[i])
	{
		if (first_word)
			first_word = false;
		else
			printf(" ");
		printf("%s", command[i]);
		i++;
	}
	if (!no_newline)
		printf("\n");
}

void	echo(char **command, t_token *token_lst, int fd_in, int fd_out)
{
	int		i;
	bool	no_newline;
	pid_t	pid;

	no_newline = false;
	i = 1;
	check_newline(command, &i, &no_newline);
	pid = fork();
	info()->exit_pid = pid;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		dup_info(token_lst, fd_in, fd_out);
		echo_output(command, i, no_newline);
		exit(0);
	}
	else
		wait(NULL);
	info()->error_code = 0;
}
