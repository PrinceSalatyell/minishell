/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:51:47 by salatiel          #+#    #+#             */
/*   Updated: 2023/04/09 17:15:08 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(char **command)
{
	char	*path;
	int		length;

	if (command[1] && command[1][0] == '-' && command[1][1])
		printf("minishell: pwd: -%c: invalid option\n\
pwd: usage: pwd [no options]\n", command[1][1]);
	else
	{
		length = 100;
		path = malloc(sizeof(char) * length);
		getcwd(path, length);
		printf("%s\n", path);
		free(path);
	}
}
