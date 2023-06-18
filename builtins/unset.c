/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:12:39 by salatiel          #+#    #+#             */
/*   Updated: 2023/06/18 20:07:20 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **command, t_token *token_lst)
{
	int		i;
	char	*key;

	i = 0;
	if (!check_pipe(token_lst))
	{
		while (command[++i])
		{
			key = get_key(command[i]);
			ft_dictdel(&(info()->env), key);
			free(key);
		}
	}
	info()->error_code = 0;
}

void	free_env(void)
{
	t_dict	*temp;
	t_dict	*temp2;

	temp = info()->env;
	while (temp)
	{
		temp2 = temp->next;
		if (temp->key)
			free(temp->key);
		if (temp->value && *(temp->value))
			free(temp->value);
		free(temp);
		temp = temp2;
	}
}
