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

void	read_from_pipe(int fd)
{
	char	buffer[BUFFER_SIZE_HD + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE_HD);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			write(1, buffer, bytes_read);
		}
	}
}

void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	heredoc(char *delimiter)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	if (fork() == 0)
	{
		close(fd[0]);
		write_to_pipe(fd[1], delimiter);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		read_from_pipe(fd[0]);
		close(fd[0]);
	}
}

