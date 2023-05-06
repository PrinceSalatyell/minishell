/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:22:46 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/06 22:14:33 by salatiel         ###   ########.fr       */
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

void	change_directory(char *path)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (!*path)
	{
		free(current_path);
		return ;
	}
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

void	cd(char **command)
{
	char	*home;

	home = get_home();
	if (command[1] && command[2])
		printf("minishell: cd: too many arguments\n");
	else if (!command[1])
	{
		if (info()->home_set)
			change_directory(home);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if (!ft_strcmp(command[1], "~"))
		change_directory(home);
	else
		change_directory(command[1]);
}
