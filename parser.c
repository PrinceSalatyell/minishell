/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 19:07:22 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_cmd(t_token *token_lst, char **cmd, int cmd_nr)
{
	if (cmd_nr == 1 && !token_lst->next)
	{
		//just execute
		execute(cmd);
	}
	else if (cmd_nr == 1 && token_lst->next)
	{
		//execute and redirect
	}
	else if (cmd_nr != 1 && token_lst-> next)
	{
		//read dup, execute and redirect
	}
	else if (cmd_nr != 1 && !token_lst-> next)
	{
		// read dup and execute
	}
}

void	simple_redirection(t_token *token_lst, char **cmd, int cmd_nr)
{
	// check if <, >, <<, >>
	(void)token_lst;
	(void)cmd;
	(void)cmd_nr;
}

void	multi_redirection(t_token *token_lst, char **cmd, int cmd_nr)
{
	(void)token_lst;
	(void)cmd;
	(void)cmd_nr;
}

void	parse_redirection(t_token *token_lst, char **cmd, int cmd_nr)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
			counter++;
	}
	if (counter == 1)
		simple_redirection(token_lst, cmd, cmd_nr);
	else
		multi_redirection(token_lst, cmd, cmd_nr);
}

void	check_command_type(t_token *token_lst, char **cmd, int cmd_nr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
		{
			parse_redirection(token_lst, cmd, cmd_nr);
			flag = 1;
			return ;
		}
		i++;
	}
	if (flag == 0)
		execute_simple_cmd(token_lst, cmd, cmd_nr);
}

void	parse_commands(t_token *token_lst)
{
	int	cmd_nr;

	cmd_nr = 1;
	while (token_lst)
	{
		check_command_type(token_lst, token_lst->value, cmd_nr);
		cmd_nr++;
		token_lst = token_lst->next;
	}
}