/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:36 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:00:53 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(int code)
{
	free_env();
	exit(code);
}

void	export_variables(char **command, char *key, int i)
{
	while (command[++i])
	{
		if (command[i][0] == '=')
		{
			printf("minishell: export: `=': not a valid identifier\n");
			info()->error_code = 999;
			continue ;
		}
		key = get_key(command[i]);
		if (ft_strchr(command[i], '='))
		{
			ft_dictdel(&(info()->env), key);
			if (*(ft_strchr(command[i], '=') + 1) == '\0')
				ft_dictadd_back(&(info()->env), \
				ft_dictnew(key, ""));
			else
				ft_dictadd_back(&(info()->env), ft_dictnew(key, \
				get_value(command[i])));
		}
		else
			if (!search_for_variable(key))
				ft_dictadd_back(&(info()->env), \
				ft_dictnew(key, NULL));
	}
}

char	*check_path(char **path_split, char *cmd)
{
	char	*command;
	int		i;

	i = -1;
	while (path_split && path_split[++i])
	{
		command = ft_strjoin_sep(path_split[i], cmd, '/');
		if (access(command, F_OK) == 0)
		{
			free_path(path_split);
			return (command);
		}
		free(command);
	}
	return (NULL);
}
