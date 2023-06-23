/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:37:59 by salatiel          #+#    #+#             */
/*   Updated: 2023/06/23 13:25:40 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_of_env(void)
{
	int		size;
	t_dict	*temp;

	size = 0;
	temp = info()->env;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

char	**create_env_list(void)
{
	char	**env_list;
	int		size;
	char	*str;
	t_dict	*temp;
	int		i;

	i = 0;
	temp = info()->env;
	size = size_of_env();
	env_list = malloc(sizeof(char *) * (size + 1));
	while (temp)
	{
		str = ft_strjoin_sep(temp->key, temp->value, '=');
		env_list[i] = str;
		i++;
		temp = temp->next;
	}
	env_list[i] = NULL;
	return (env_list);
}

void	free_env_list(char **env_list)
{
	int	i;

	i = -1;
	while (env_list[++i])
		free(env_list[i]);
	free(env_list);
}

char	*get_path(void)
{
	t_dict	*temp;
	char	*path;

	temp = info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PATH"))
		{
			path = temp->value;
			return (path);
		}
		temp = temp->next;
	}
	return (NULL);
}
