/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/05/01 01:30:52 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocs()
{

}

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
		if (fd != -1)
			close(fd);
		if (cmd_red[i][0] == '<')
		{
			fd = open_file(cmd_red[i + 1], 2);
			info()->file_flag = 1;
			if (fd == -1)
			{
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

//dont forget to handlde >< and <>
void	parse_redirection(t_token *token_lst, char **cmd)
{
	int	fd_in;
	int	fd_out;
	char	**cmd_matrix;

	info()->file_flag = 0;
	fd_in = get_fd_in(cmd);
	fd_out = get_fd_out(cmd);
	if (info()->file_flag == 2)
		return ;
	cmd_matrix = get_cmd_red_matrix(cmd, 0);
	if (fd_in != -1)
		info()->in_flag = TRUE;
	if (fd_out != -1)
		info()->out_flag = TRUE;
	if (cmd[0][0] != '<' && cmd[0][0] != '>')
		execute_redirection(token_lst, cmd_matrix, fd_in, fd_out);
	wait(NULL);
	close(fd_in);
	close(fd_out);
	free_matrix(cmd_matrix);
}

void	check_command_type(t_token *token_lst, char **cmd)
{
	int	i;

	info()->in_flag = FALSE;
	info()->out_flag = FALSE;
	info()->fd_red = FALSE;
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
		execute_simple_cmd(token_lst, cmd);
}

void	parse_commands(t_token *token_lst)
{
	int	j;

	info()->cmd_nr = 0;
	info()->fd_pipe = get_pipe_fd();
	while (token_lst)
	{
		if (check_if_invalid(token_lst->value))
			break ;
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			check_command_type(token_lst, token_lst->value);
			info()->cmd_nr++;
		}
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
		wait(NULL);
}