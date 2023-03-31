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

// void	send_simple_command(t_token *token_lst, int command_len, int nr_commands)
// {
// 	//char	**simple_cmd;
// 	int	len;

// 	(void)nr_commands;
// 	(void)command_len;
// 	(void)token_lst;
// 	len = 0;
// }

// int	get_command_len(t_token **token_lst)
// {
// 	int	len;

// 	len = 0;
// 	if (*token_lst)
// 	{
// 		while (*token_lst && ft_strcmp((*token_lst)->type, "Operator") != 0)
// 		{
// 			len++;
// 			*token_lst = (*token_lst)->next;
// 		}
// 		if (*token_lst)
// 			*token_lst = (*token_lst)->next;
// 	}
// 	return (len);
// }

// int	check_nr_commands(t_token *token_lst)
// {
// 	int	len;

// 	len = 0;
// 	if (token_lst)
// 	{
// 		while (token_lst)
// 		{
// 			if (ft_strcmp(token_lst->type, "Command") == 0)
// 				len++;
// 			token_lst = token_lst->next;
// 		}
// 	}
// 	return (len);
// }

void	parse_commands(t_token *token_lst)
{
	//int	nr_commands;
	//int	command_len;
	execute(token_lst);
	// else
	// 	execute_pipe(token_lst);
// 	nr_commands = check_nr_commands(token_lst);
// 	while (nr_commands)
// 	{
// 		//command_len = get_command_len(&temp);
// 		//send_simple_command(token_lst, command_len, nr_commands);
// 		nr_commands--;
// 	}
}
