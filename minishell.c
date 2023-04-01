/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:50 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 13:32:14 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changes Ctrl+C to \n
void	sig_handler(int n)
{
	(void)n;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
}

int	main(void)
{
	ignore_signal();
	while (1)
	{
		get_input();
		if (_input()->command[0] != '\0')
		{
			analyze_and_parse(_input()->command);
			free_token_matrix();
		}
		free(_input()->command);
	}
	return (0);
}
