/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:38:33 by salatiel          #+#    #+#             */
/*   Updated: 2023/04/02 21:27:34 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char **command)
{
	int	size;

	size = 0;
	while (command[size])
		size++;
	if (size == 1)
		print_export(0, NULL);
	else
		add_to_env(command);
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
		printf("declare -x ");
		printf("%s=\"%s\"\n", print->key, print->value);
	}
}

void	add_to_env(char **command)
{
	int	i;

	i = -0;
	while (command[++i])
	{
		if (ft_strchr(command[i], '='))
			ft_dictadd_back(&(info()->env), ft_dictnew(get_key(command[i]), \
			get_value(command[i])));
		else
			ft_dictadd_back(&(info()->env), \
			ft_dictnew(get_key(command[i]), ""));
	}
}
