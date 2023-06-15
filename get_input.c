/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:02:01 by josanton          #+#    #+#             */
/*   Updated: 2023/06/10 22:49:56 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_promt(char *str, int flag)
{
	char	*command;
	char	*tmp_command;

	tmp_command = NULL;
	if (flag == 1)
		tmp_command = readline(YELLOW"dquote> " COLOUR_END);
	else if (flag == 2)
		tmp_command = readline(YELLOW"squote> " COLOUR_END);
	else if (flag == 3)
		tmp_command = readline(YELLOW"pipe> " COLOUR_END);
	if (!tmp_command)
	{
		free(tmp_command);
		free(str);
		printf("\n");
		exit(0);
	}
	command = ft_strjoin_nl(str, tmp_command);
	free(tmp_command);
	check_if_complete(command);
}

// void	check_if_exit(char *str)
// {
	
// }

void	get_input(void)
{
	char	*tmp_command;

	tmp_command = readline(BLUE"minishell" RED ">$ " COLOUR_END);
	if (!tmp_command)
	{
		free(tmp_command);
		printf("\n");
		exit(0);
	}
	check_if_complete(tmp_command);
	if (_input()->command[0] == '\0')
		return ;
	//check_if_exit(_input()->command);
	if (!strcmp(_input()->command, "exit"))
	{
		free(_input()->command);
		exit(1);
	}
	if (_input()->command && *_input()->command)
		add_history(_input()->command);
}
