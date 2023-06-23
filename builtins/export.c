/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:38:33 by salatiel          #+#    #+#             */
/*   Updated: 2023/06/23 12:59:42 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char **command, t_token *token_lst, int fd_in, int fd_out)
{
	pid_t	pid;

	if (!command[1])
	{
		pid = fork();
		info()->exit_pid = pid;
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			dup_info(token_lst, fd_in, fd_out);
			print_export(0, NULL);
			exit(0);
		}
		else
			wait(NULL);
	}
	else
		add_to_env(command, token_lst);
	if (info()->error_code == 999)
		info()->error_code = 1;
	else
		info()->error_code = 0;
}

void	print_it(char *key, char *value)
{
	printf("declare -x ");
	if (value)
		printf("%s=\"%s\"\n", key, value);
	else
		printf("%s\n", key);
}

void	print_export(int size, char *last_printed)
{
	t_dict	*print;
	t_dict	*temp;

	size = ft_dictsize(info()->env);
	while (size--)
	{
		temp = info()->env;
		print = temp;
		while (temp->next)
		{
			if (last_printed && ft_strcmp(print->key, last_printed) <= 0)
				print = temp->next;
			if (last_printed && ft_strcmp(temp->next->key, last_printed) <= 0)
			{
				temp = temp->next;
				continue ;
			}
			else if (ft_strcmp(temp->next->key, print->key) < 0)
				print = temp->next;
			temp = temp->next;
		}
		last_printed = print->key;
		print_it(print->key, print->value);
	}
}

bool	search_for_variable(char *key)
{
	t_dict	*temp;

	temp = info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			free(key);
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

void	add_to_env(char **command, t_token *token_lst)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	if (!check_pipe(token_lst))
	{
		export_variables(command, key, i);
	}
}
