/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:22:46 by salatiel          #+#    #+#             */
/*   Updated: 2023/04/09 15:44:55 by salatiel         ###   ########.fr       */
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

void	change_directory(char *path)
{
	if (!*path)
		return ;
	if (chdir(path))
		perror("minishell");
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
