/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:38:33 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/06 23:11:18 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char **command)
{
	int		size;
	pid_t	pid;

	size = 0;
	while (command[size])
		size++;

	if (size == 1)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			print_export(0, NULL);
			exit(0);
		}
		else
			wait(NULL);
	}
	else
		add_to_env(command);
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
			else if (strcmp(temp->next->key, print->key) < 0)
				print = temp->next;
			temp = temp->next;
		}
		last_printed = print->key;
		print_it(print->key, print->value);
	}
}

void	add_to_env(char **command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[++i])
	{
		key = get_key(command[i]);
		ft_dictdel(&(info()->env), key);
		if (ft_strchr(command[i], '='))
		{
			if (*(ft_strchr(command[i], '=') + 1) == '\0')
				ft_dictadd_back(&(info()->env), \
				ft_dictnew(key, ""));
			else
				ft_dictadd_back(&(info()->env), ft_dictnew(key, \
				get_value(command[i])));
		}
		else
			ft_dictadd_back(&(info()->env), \
			ft_dictnew(key, NULL));
	}
}
