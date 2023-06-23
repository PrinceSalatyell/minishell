/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:20:44 by timartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:28:16 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_pipe(t_token *token_lst)
{
	int	i;

	while (token_lst)
	{
		i = -1;
		while (token_lst->value[++i])
		{
			if (!ft_strcmp(token_lst->value[i], "|"))
				return (true);
		}
		token_lst = token_lst->next;
	}
	return (false);
}

// fd[0] - read
// fd[1] - write
void	dup_info(t_token *token_lst, int fd_in, int fd_out)
{
	int	j;

	if (fd_in > 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (info()->cmd_nr != 0)
		dup2(info()->fd_pipe[info()->cmd_nr - 1][0], STDIN_FILENO);
	if (fd_out > 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (token_lst->next)
		dup2(info()->fd_pipe[info()->cmd_nr][1], STDOUT_FILENO);
	j = -1;
	while (++j < info()->nr_pipe)
	{
		close(info()->fd_pipe[j][0]);
		close(info()->fd_pipe[j][1]);
	}
}

char	**get_cmd_red_matrix(char **cmd_red, int j, int i, int len)
{
	char	**cmd_matrix;

	len = get_cmd_red_len(cmd_red);
	cmd_matrix = malloc(sizeof(char *) * (len + 1));
	if (!cmd_matrix)
		return (NULL);
	cmd_matrix[len] = NULL;
	while (cmd_red[i] != NULL)
	{
		if (cmd_red[i][0] != '>' && cmd_red[i][0] != '<')
		{
			if ((cmd_red[i][0] == '"' || cmd_red[i][0] == 39)
				&& (cmd_red[i][1] == '>' || cmd_red[i][1] == '<'))
				cmd_matrix[i] = cpy_cmd_red_matrix(cmd_red, i);
			else
				cmd_matrix[j] = ft_strdup(cmd_red[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	return (cmd_matrix);
}

int	get_cmd_red_len(char **cmd_red)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd_red[i])
	{
		if (cmd_red[i][0] != '>' && cmd_red[i][0] != '<')
			len++;
		else
			i++;
		i++;
	}
	return (len);
}

int	**get_pipe_fd(void)
{
	int	**fd;
	int	i;

	fd = malloc(sizeof(int *) * info()->nr_pipe);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < info()->nr_pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i < info()->nr_pipe)
	{
		if (pipe(fd[i]) == -1)
			return (NULL);
		i++;
	}
	return (fd);
}
