#include "minishell.h"

void	dup_bult_in(t_token *token_lst)
{
	int	j;

	if (info()->cmd_nr != 0)
		dup2(info()->fd[info()->cmd_nr - 1][0], STDIN_FILENO);
	if (token_lst->next)
		dup2(info()->fd[info()->cmd_nr][1], STDOUT_FILENO);
	j = -1;
	while (++j < info()->nr_pipe)
	{
		close(info()->fd[j][0]);
		close(info()->fd[j][1]);
	}
}

char    **get_cmd_red_matrix(char **cmd_red, int j)
{
	char    **cmd_matrix;
	int i;
	int len;
	//int arg_len;

	len = get_cmd_red_len(cmd_red);
	cmd_matrix = malloc(sizeof(char*) * len + 1);
	if (!cmd_matrix)
		return (NULL);
	cmd_matrix[len] = NULL;
	i = 0;
	while (cmd_red[i] != NULL)
	{
		if (cmd_red[i][0] != '>' && cmd_red[i][0] != '<')
		{
			//arg_len = ft_strlen(cmd_red[i]);
			cmd_matrix[j] = ft_strdup(cmd_red[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	return (cmd_matrix);
}

int get_cmd_red_len(char **cmd_red)
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

	fd = malloc(sizeof(int*) * info()->nr_pipe);
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