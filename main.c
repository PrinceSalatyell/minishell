/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:50:59 by josanton          #+#    #+#             */
/*   Updated: 2023/03/20 19:01:26 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *line, char *first_word)
{
	char	**str;

	if (!ft_strcmp(first_word, "echo"))
	{
		str = ft_split(line, ' ');
		return (echo(str[1], true));
	}
	return (false);
}

bool	parse_line(char *line)
{
	char	*first_word;

	first_word = ft_first_word(line);
	if (ft_strnstr(BUILTIN, first_word, 33))
		return (is_builtin(line, first_word));
	else
		return (false);
}

int	main(void)
{
	char	*line;

	line = readline(BLUE "minishell" RED " >$ " COLOUR_END);
	while (line != NULL)
	{
		if (!parse_line(line))
			printf("minishell: command not found: %s\n", line);
		add_history(line);
		free(line);
		line = readline(BLUE "minishell" RED ">$ " COLOUR_END);
	}
	return (0);
}
