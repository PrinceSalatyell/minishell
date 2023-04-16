/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:22:24 by salatiel          #+#    #+#             */
/*   Updated: 2023/04/16 17:56:53 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **command)
{
	int		i;
	bool	word_found;

	word_found = false;
	i = 0;
	while (command[++i])
	{
		while (command[i] && !ft_strcmp(command[i], "-n") && !word_found)
			i++;
		if (!command[i])
			break ;
		if (!ft_strcmp(command[1], "-n"))
		{
			if (ft_strcmp(command[i - 1], "-n") || word_found)
				printf(" ");
		}
		else
			if (i != 1)
				printf(" ");
		printf("%s", command[i]);
		word_found = true;
	}
	if (!command[1])
		printf("\n");
	else if (ft_strcmp(command[1], "-n"))
		printf("\n");
}
