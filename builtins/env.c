/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:16:08 by josanton          #+#    #+#             */
/*   Updated: 2023/04/01 17:38:26 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *env_line)
{
	int		i;
	char	*value;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	value = ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1);
	return (value);
}

char	*get_key(char *env_line)
{
	int		i;
	char	*key;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	key = ft_substr(env_line, 0, i);
	return (key);
}

void	store_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;

	key = get_key(envp[0]);
	value = get_value(envp[0]);
	(info()->env) = ft_dictnew(key, value);
	i = 0;
	while (envp[++i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
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
