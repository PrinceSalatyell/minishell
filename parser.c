/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/06/10 22:50:27 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	redirect_out(char **cmd_red, int open_flag)
// {
// 	int	i;
// 	int	fd;
// 	char	**cmd_matrix;

// 	i = 0;
// 	fd = -1;
// 	while (cmd_red[i])
// 	{
// 		if (cmd_red[i][0] == '>')
// 		{
// 			if (fd != -1)
// 				close(fd);
// 			if (cmd_red[i][1] == '>')
// 				fd = open_file(cmd_red[i + 1], open_flag);
// 			else
// 				fd = open_file(cmd_red[i + 1], open_flag);
// 			while (cmd_red[i + 1] && cmd_red[i + 1][0] != '>')
// 				i++;	
// 		}
// 		i++;
// 	}
// 	cmd_matrix = get_cmd_red_matrix(cmd_red, 0);
// 	execute_redirection_out(cmd_matrix, fd, 1);
// 	close(fd);
// 	wait(NULL);
// 	free_matrix(cmd_matrix);
// }

// void	redirect_in(char **cmd_red, int open_flag)
// {
// 	int	i;
// 	int	fd;
// 	char	**cmd_matrix;

// 	// i = -1;
// 	// while (cmd_red[++i])
// 	// 	printf("cmd -> %s\n", cmd_red[i]);
// 	fd = -1;
// 	i = 0;
// 	while (cmd_red[i])
// 	{
// 		if (fd != -1)
// 			close(fd);
// 		if (cmd_red[i][0] == '<')
// 		{
// 			fd = open_file(cmd_red[i + 1], open_flag);
// 			if (fd == -1)
// 				printf("%s: file does not exist\n", cmd_red[i + 1]);
// 			while (cmd_red[i + 1] && cmd_red[i + 1][0] != '<')
// 				i++;
// 		}
// 		i++;
// 	}
// 	if (fd == -1)
// 		return ;
// 	cmd_matrix = get_cmd_red_matrix(cmd_red, 0);
// 	execute_redirection_in(cmd_matrix, fd);
// 	wait(NULL);
// 	free_matrix(cmd_matrix);
// 	close(fd);
// }

int	get_fd_in(char **cmd_red)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (cmd_red[i])
	{
		if (cmd_red[i][0] == '<')
		{
			if (fd != -1)
				close(fd);
			if (cmd_red[i][1] == '<')
				fd = heredoc(cmd_red[i + 1]);
			else
				fd = open_file(cmd_red[i + 1], 2);
			info()->file_flag = 1;
			if (fd == -1)
			{
				if (info()->here_flag == FALSE)
					printf("%s: file does not exist\n", cmd_red[i + 1]);
				info()->file_flag = 2;
				return (fd);
			}
			while (cmd_red[i + 1] && cmd_red[i + 1][0] != '<')
				i++;
		}
		i++;
	}
	return (fd);
}

int	get_fd_out(char **cmd_red)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (cmd_red[i])
	{
		if (cmd_red[i][0] == '>')
		{
			if (fd != -1)
				close(fd);
			if (cmd_red[i][1] == '>')
				fd = open_file(cmd_red[i + 1], 1);
			else
				fd = open_file(cmd_red[i + 1], 0);
			while (cmd_red[i + 1] && cmd_red[i + 1][0] != '>')
				i++;	
		}
		i++;
	}
	return (fd);
}

void	parse_redirection(t_token *token_lst, char **cmd)
{
	int	fd_in;
	int	fd_out;
	char	**cmd_matrix;
	int		exit_status;

	info()->file_flag = 0;
	info()->exit_redirection = true;
	fd_in = get_fd_in(cmd);
	fd_out = get_fd_out(cmd);
	if (info()->file_flag == 2)
		return ;
	cmd_matrix = get_cmd_red_matrix(cmd, 0);
	if (cmd_matrix[0])
		execute(token_lst, cmd_matrix, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
	if (!info()->cmd_nr)
	{
		waitpid(info()->exit_pid, &exit_status, 0);
		if (!info()->builtin)
			info()->error_code = WEXITSTATUS(exit_status);
	}
}

void	check_command_type(t_token *token_lst, char **cmd)
{
	int	i;
	char	**new_cmd;

	new_cmd = NULL;
	info()->cmd_not_found = false;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
			break ;
		i++;
	}	
	if (cmd[i])
		parse_redirection(token_lst, cmd);
	else
	{
		new_cmd = rm_red_quotes(cmd);
		execute(token_lst, new_cmd, 0, 0);
	}
}

void	parse_commands(t_token *token_lst)
{
	int	j;
	int	exit_status;

	info()->here_flag = FALSE;
	info()->cmd_nr = 0;
	info()->fd_pipe = get_pipe_fd();
	while (token_lst)
	{
		if (check_invalid_red(token_lst->value))
			break ;
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			check_command_type(token_lst, token_lst->value);
			info()->cmd_nr++;
		}
		info()->here_flag = FALSE;
		token_lst = token_lst->next;
	}
	j = -1;
	while (++j < info()->nr_pipe)
	{
		close(info()->fd_pipe[j][0]);
		close(info()->fd_pipe[j][1]);
	}
	free_fd(info()->fd_pipe);
	j = -1;
	while (++j < info()->nr_pipe + 1)
	{
		waitpid(info()->exit_pid, &exit_status, 0);
		if (!info()->builtin && !info()->exit_redirection && !info()->cmd_not_found)
			info()->error_code = WEXITSTATUS(exit_status);
		else if (info()->exit_redirection)
			info()->exit_redirection = false;
	}
}
