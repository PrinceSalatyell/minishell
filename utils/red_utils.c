/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:25:37 by timartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:25:48 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// flag -> 0 - WR_TRUNC | 1 - WR_APPEND | 2 - RDONLY 
int	open_file(char *file, int flag)
{
	char	*full_path;
	int		fd;

	fd = 0;
	full_path = get_dir_path(file);
	if (flag == 0)
		fd = open(full_path, O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag == 1)
		fd = open(full_path, O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag == 2)
		fd = open(full_path, O_RDONLY | O_CLOEXEC);
	free(full_path);
	return (fd);
}

int	check_invalid_red(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' && cmd[i][1] == '<')
		{
			printf("Unexpected token '><'\n");
			info()->error_code = 2;
			return (1);
		}
		if (cmd[i][0] == '<' && cmd[i][1] == '>')
		{
			printf("Unexpected token '<>'\n");
			info()->error_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*cpy_cmd_red_matrix(char **cmd_red, int i)
{
	char	*str;
	int		len;

	len = ft_strlen(cmd_red[i]);
	str = malloc(sizeof(char) * (len - 1));
	if (!str)
		return (NULL);
	str = ft_strncpy(str, cmd_red[i] + 1, len - 2);
	str[len - 2] = '\0';
	return (str);
}

void	wait_pipes(void)
{
	int	exit_status;
	int	j;

	j = -1;
	while (++j < info()->nr_pipe + 1)
	{
		waitpid(info()->exit_pid, &exit_status, 0);
		if (!info()->builtin && !info()->exit_redirection
			&& !info()->cmd_not_found)
			info()->error_code = WEXITSTATUS(exit_status);
		else if (info()->exit_redirection)
			info()->exit_redirection = false;
	}
}
