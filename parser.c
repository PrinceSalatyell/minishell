/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 12:06:13 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(t_token *token_lst)
{
	int	nr_commands;

	nr_commands = 0;
	if (token_lst)
	{
		while (token_lst->next)
		{
			if (ft_strcmp(token_lst->type, "Operator") == 0)
				nr_commands++;
			token_lst = token_lst->next;
		}
	}
	printf("nr_commands - %d\n", nr_commands);
}