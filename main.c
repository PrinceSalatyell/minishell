/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:50:59 by josanton          #+#    #+#             */
/*   Updated: 2023/03/20 14:14:46 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = readline(BLUE "minishell> " COLOUR_END);
	while (line != NULL)
	{
		printf("%s\n", line);
		add_history(line);
		free(line);
		line = readline(BLUE "minishell> " COLOUR_END);
	}

	return (0);
}
