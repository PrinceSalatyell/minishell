/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:16:08 by josanton          #+#    #+#             */
/*   Updated: 2023/06/18 19:57:18 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *env_line)
{
	int		i;
	char	*value;

	if (env_line == NULL)
		return (NULL);
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

	if (env_line == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	key = ft_substr(env_line, 0, i);
	return (key);
}

void	empty_env(void)
{
	(info()->env) = ft_dictnew("PWD", getcwd(NULL, 0));
	ft_dictadd_back(&(info()->env), \
	ft_dictnew("SHLVL", ft_itoa(info()->shlvl)));
	ft_dictadd_back(&(info()->env), \
	ft_dictnew("OLDPWD", NULL));
}

void	store_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;

	if (!*envp)
	{
		empty_env();
		return ;
	}
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
	ft_dictdel(&(info()->env), "SHLVL");
	ft_dictadd_back(&(info()->env), \
	ft_dictnew(ft_strdup("SHLVL"), ft_itoa(info()->shlvl)));
	(info()->path) = get_path();
}

void	env(t_token *token_lst, int fd_in, int fd_out)
{
	t_dict	*temp;
	int		pid;

	pid = fork();
	info()->exit_pid = pid;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		dup_info(token_lst, fd_in, fd_out);
		temp = info()->env;
		while (temp)
		{
			if (temp->value)
				printf("%s=%s\n", temp->key, temp->value);
			temp = temp->next;
		}
		exit (0);
	}
	info()->error_code = 0;
}
