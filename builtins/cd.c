/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:22:46 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/09 23:04:56 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(void)
{
	t_dict	*temp;

	temp = info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "HOME"))
		{
			info()->home_set = true;
			return (temp->value);
		}
		temp = temp->next;
	}
	info()->home_set = false;
	return (info()->home);
}

void	change_pwd(char *to_change, char *new_value)
{
	t_dict	*temp;

	temp = info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, to_change))
		{
			free(temp->value);
			temp->value = ft_substr(new_value, 0, ft_strlen(new_value));
		}
		temp = temp->next;
	}
}

void	change_directory(char *path, t_token *token_lst)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (!*path)
	{
		free(current_path);
		return ;
	}
	if (!check_pipe(token_lst))
	{
		if (chdir(path))
		{
			perror("minishell");
			free(current_path);
		}
		else
		{
			change_pwd("OLDPWD", current_path);
			free(current_path);
			current_path = getcwd(NULL, 0);
			change_pwd("PWD", current_path);
			free(current_path);
		}
	}
}

char	*get_old_pwd(void)
{
	t_dict	*temp;
	char	*old_pwd;

	old_pwd = "";
	temp = info()->env;
	while (temp)
	{
		if (!strcmp(temp->key, "OLDPWD"))
		{
			old_pwd = temp->value;
		}
		temp = temp->next;
	}
	return (old_pwd);
}

void	cd(char **command, t_token *token_lst)
{
	char	*home;

	home = get_home();
	if (command[1] && command[2])
		printf("minishell: cd: too many arguments\n");
	else if (!command[1])
	{
		if (info()->home_set)
			change_directory(home, token_lst);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if (!ft_strcmp(command[1], "~"))
		change_directory(home, token_lst);
	else if (!ft_strcmp(command[1], "-"))
		change_directory(get_old_pwd(), token_lst);
	else
		change_directory(command[1], token_lst);
}
