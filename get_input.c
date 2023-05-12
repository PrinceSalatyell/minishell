/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:02:01 by josanton          #+#    #+#             */
/*   Updated: 2023/05/12 18:21:32 by salatiel         ###   ########.fr       */
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
	command = ft_strjoin_nl(str, tmp_command);
	free(tmp_command);
	check_if_complete(command);
}

void	get_input(void)
{
	char	*tmp_command;

	tmp_command = readline(BLUE"minishell" RED ">$ " COLOUR_END);
	if (!tmp_command)
		exit(0);
	check_if_complete(tmp_command);
	if (_input()->command[0] == '\0')
		return ;
	if (_input()->command == NULL || !strcmp(_input()->command, "exit"))
	{
		write(1, "\n", 1);
		free(_input()->command);
		exit(1);
	}
	if (_input()->command && *_input()->command)
		add_history(_input()->command);
}
