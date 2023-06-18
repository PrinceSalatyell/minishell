/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:12:39 by salatiel          #+#    #+#             */
/*   Updated: 2023/06/18 00:36:09 by salatiel         ###   ########.fr       */
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

void	free_env()
{
	t_dict	*temp;

	temp = info()->env;
	while (temp)
	{
		free(temp->key);
		free(temp->value);
		temp = temp->next;
	}
}