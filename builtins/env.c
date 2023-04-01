/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:16:08 by josanton          #+#    #+#             */
/*   Updated: 2023/04/01 16:07:49 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;

	key = ft_split(envp[0], '=')[0];
	value = ft_split(envp[0], '=')[1];
	(info()->env) = ft_dictnew(key, value);
	i = 0;
	while (envp[++i])
	{
		key = ft_split(envp[i], '=')[0];
		value = ft_split(envp[i], '=')[1];
		ft_dictadd_back(&(info()->env), ft_dictnew(key, value));
	}
}

void	env(void)
{
	t_dict	*temp;

	temp = info()->env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
