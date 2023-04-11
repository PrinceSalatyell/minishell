#include "minishell.h"

char    **get_next_command(char **cmd, int *i)
{
    char    **cmd_matrix;
    int j;
    int len;
    int arg_len;

    len = get_redirection_len(cmd, *i);
    cmd_matrix = malloc(sizeof(char*) * len + 1);
	if (!cmd_matrix)
		return (NULL);
	cmd_matrix[len] = NULL;
    j = 0;
    while (j < len)
	{
		arg_len = ft_strlen(cmd[*i]);
		cmd_matrix[j] = ft_strdup(cmd[*i]);
		j++;
        *i = *i + 1;
	}
    return (cmd_matrix);
}

int get_redirection_len(char **cmd, int i)
{
    int	len;

	len = 0;
	while (cmd[i] && cmd[i][0] != '<' && cmd[i][0] != '>')
	{
		len++;
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