/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:07:12 by salatiel          #+#    #+#             */
/*   Updated: 2023/05/12 21:36:59 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	info()->here_flag = TRUE;
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

