/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 19:07:22 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocs()
{

}

void	redirect_in()
{

}

char	*get_dir_path(char *cmd)
{
	char	*path;
	char	*file;

	path = NULL;
	path = getcwd(path, 100);
	if (!path)
		return (NULL);

	file = ft_strjoin_sep(path, cmd, '/');
	free(path);
	return (file);
}

// flag -> 0 - TRUNC | 1 - APPEND
int	open_file(char *file, int flag)
{
	char	*full_path;
	int	fd;

	fd = 0;
	full_path = get_dir_path(file);
	if (flag == 0)
		fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 1)
		fd = open(full_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free(full_path);
	return (fd);
}

void	redirect_out(char **cmd)
{
	int	i;
	int	fd;
	char	**red_cmd;

	i = 0;
	fd = -1;
	while (cmd[i])
	{
		if (cmd[i][0] == '>')
		{
			if (fd != -1)
				close(fd);
			if (cmd[i][1] == '>')
				fd = open_file(cmd[i + 1], 1);
			else
				fd = open_file(cmd[i + 1], 0);
		}	
		i++;
	}
	i = 0;
	red_cmd = get_next_command(cmd, &i);
	execute_redirection(red_cmd, fd);
	close(fd);
	wait(NULL);
	free_matrix(red_cmd);
}

//dont forget to handlde >< and <>
void	simple_redirection(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>')
		{
			// if (cmd[i][1] == '>' )
			// 	redirect_append();
			// else
			// {
			redirect_out(cmd);
			return ;
			// }
		}
		else if (cmd[i][0] == '<')
		{
			if (cmd[i][1] == '<')
				heredocs();
			else
				redirect_in();
		}
		i++;
	}
}

void	multi_redirection(t_token *token_lst, char **cmd)
{
	(void)token_lst;
	(void)cmd;
}

void	parse_redirection(t_token *token_lst, char **cmd)
{
	int	i;
	int	counter;

	i = 0;
	(void)token_lst;
	//len = get_redirection_len(cmd, i);
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
			counter++;
		i++;
	}
	// if (counter == 1)
	simple_redirection(cmd);
	// else
	// 	multi_redirection(token_lst, cmd);
}

void	check_command_type(t_token *token_lst, char **cmd, int **fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
		{
			parse_redirection(token_lst, cmd);
			flag = 1;
			return ;
		}
		i++;
	}
	if (flag == 0)
		execute_simple_cmd(token_lst, cmd, fd);
}

void	parse_commands(t_token *token_lst)
{
	int	**fd;
	int	j;

	info()->cmd_nr = 0;
	fd = get_pipe_fd();
	while (token_lst)
	{
		if (ft_strcmp(token_lst->type, "Command") == 0)
		{
			check_command_type(token_lst, token_lst->value, fd);
			info()->cmd_nr++;
		}
		token_lst = token_lst->next;
	}
	j = -1;
	while (++j < info()->nr_pipe)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	free_fd(fd);
	j = -1;
	while (++j < info()->nr_pipe + 1)
		wait(NULL);
}